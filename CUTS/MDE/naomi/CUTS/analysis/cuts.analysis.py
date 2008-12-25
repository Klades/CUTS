# -*- Python -*-

###############################################################################
#
# @file             cuts.analysis.py
#
# $Id$
#
# @author           James H. Hill
#
###############################################################################

import sys
import httplib
import getopt
import xml.dom.minidom

__doc__ = """CUTS BMW service and analysis client connector for NAOMI

Usage: cuts.analysis.py [OPTIONS]

Connection Options:
  --server=HOST                connect to BMW at location HOST[:PORT]
  --username=VALUE             username for login to server
  --password=VALUE             password to use when connecting to server

NAOMI Options:
  -l, --list-attributes        list NAOMI attributes for model
  -u, --update-attributes      update all attributes for the model
  -p, --attribute-path=PATH    location of the attibutes on disk
  --interface-basename=PATH    path of interface file, excluding
                               _interface.xml suffix
  --owner=NAME                 NAME is the owner of the attributes

BMW Options:
  --test-suite=NAME            use attributes in test suite NAME

Information Options:
  -h, --help                   print this help message
"""

#
# @class UserCredentials
#
# Storage object for user credentials. The credentials are the username
# and password set to the web service.
#
class UserCredentials (object):
  def __init__ (self, username=None, password=None):
    self.username = username
    self.password = password

#
# main
#
def main ():
  try:
    short_opt = "hlup:"
    long_opt = ["help", "server=", "test-suite=",
                "list-attributes", "update-attributes",
                "attribute-path=", "owner=",
                "interface-basename=", "username=",
                "password="]

    opts, args = getopt.gnu_getopt (sys.argv[1:], short_opt, long_opt)

  except getopt.GetoptError, err:
    # print help information and exit
    print str (err)
    sys.exit (2)

  server = None
  suite = None
  update = False
  list = False
  path = None
  owner = None
  interface_basename = "."

  creds = UserCredentials ()

  # parse the command-line arguments
  for o, a in opts:
    if o == "-v":
      verbose = True
    elif o in ("-h", "--help"):
      print __doc__
      sys.exit()
    elif o in ("--server"):
      server = a
    elif o in ("--test-suite"):
      suite = a
    elif o in ("-l", "--list-attributes"):
      list = True
    elif o in ("-u", "--update-attributes"):
      update = True
    elif o in ("-p", "--attribute-path"):
      path = a
    elif o in ("--interface-basename"):
      interface_basename = a;
    elif o in ("--username"):
      creds.username = a
    elif o in ("--password"):
      creds.password = a
    elif o in ("--owner") :
      owner = a
    else:
      assert False, "unhandled option (%s)" % o

  if list:
    listNaomiAttributes (server, creds, suite)

  if update:
    attrs = updateNaomiAttributes (path, owner, server, creds, suite)
    wriateNaomiInterfaceFile (interface_basename, owner, attrs)

#
# wriateNaomiInterfaceFile
#
def wriateNaomiInterfaceFile (basename, owner, attrs):
  # open the interface file for writing
  filename = "%s_interface.xml" % basename
  f = open (filename, "w")

  # write the interface file
  f.write ("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n")
  f.write ("<interface xmlns=\"http://www.atl.lmco.com/naomi/interfaces\"\n")
  f.write ("           xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n")
  f.write ("           xsi:schemaLocation=\"http://www.atl.lmco.com/naomi/interfaces interface.xsd\">\n")
  f.write ("  <name>%s</name>\n" % owner)
  f.write ("  <type>%s</type>\n\n" % owner)
  f.write ("  <!-- attributes -->\n")
  f.write ("  <input>CUTS.test.uuid</input>\n")

  for attr in attrs:
    f.write ("  <output>%s</output>\n" % attr)

  f.write ("</interface>\n")

  # close the file
  f.close ()

#
# listNaomiAttributes
#
def listNaomiAttributes (server, creds, suite):
  attributes = getUnitTests (server, creds, suite)

  # print the only input attribute
  print " input attribute : CUTS.test.uuid"

  # print the output attributes, which are the unit tests
  for attr in attributes:
    print "output attribute : %s" % attr

#
# updateNaomiAttributes
#
def updateNaomiAttributes (path, owner, server, creds, suite):
  attrs = getUnitTests (server, creds, suite)
  uuid = readTestUUID (path)

  for attr in attrs:
    writeNaomiAttribute (path, owner, server, creds, uuid, attr)

  return attrs

#
# writeNaomiAttribute
#
def writeNaomiAttribute (path, owner, server, creds, uuid, attr):
  print "info: writing attribute %s for test %s" % (attr, uuid)

  # construct the message for the request
  message = """<EvaluateUnitTest xmlns="http://www.dre.vanderbilt.edu/CUTS">
      <UUID>%s</UUID>
      <UnitTest>%s</UnitTest>
    </EvaluateUnitTest>""" % (uuid, attr)

  # prepare the web service client
  response = sendSOAPMessage (server, creds, message, 'EvaluateUnitTest')

  if (response) :
    # convert the response into an XML document
    values = response.getElementsByTagName ("Value")

    # get the value from the response
    value = getNodeText (values[0].childNodes)

    # write the value to the XML attribute file
    filename = "%s/%s" % (path, attr)
    f = open (filename, "w")

    f.write ("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n")
    f.write ("<attribute xmlns=\"http://www.atl.lmco.com/naomi/attributes\"\n")
    f.write ("           xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n")
    f.write ("           xsi:schemaLocation=\"http://www.atl.lmco.com/naomi/attributes attribute.xsd\">\n")
    f.write ("  <owner>%s</owner>\n" % owner)
    f.write ("  <value>%s</value>\n" % value)
    f.write ("  <description>Evaluation of %s unit test</description>\n" % attr)
    f.write ("</attribute>\n")

    # close the file
    f.close ()

  else:
    print 'error: failed to evaluate unit test %s for %s' % (attr, uuid)

#
# getUnitTests
#
def getUnitTests (server, creds, suite):
  attrs = []

  message = """<ListUnitTests xmlns="http://www.dre.vanderbilt.edu/CUTS">
  <TestSuite>%s</TestSuite>
  </ListUnitTests>""" % (suite)

  response = sendSOAPMessage (server, creds, message, 'ListUnitTests')

  if (response) :
    attributes = response.getElementsByTagName ("string")

    for attr in attributes:
      attrs.append (getNodeText (attr.childNodes))

  else:
    print 'error: failed to retrieve unit tests'

  return attrs

#
# readTestUUID
#
def readTestUUID (path):
  uuid = None
  filename = "%s/%s" % (path, "CUTS.test.uuid")

  # open the XML attribute file for reading
  f = open (filename, "r")

  # read the document then close the file
  xmldoc = xml.dom.minidom.parse (f);
  f.close ()

  # locate the value attribute
  values = xmldoc.getElementsByTagName ("value")

  # get the UUID from the value tag
  uuid = getNodeText (values[0].childNodes)
  return uuid

#
# getNodeText
#
def getNodeText (nodelist):
  rc = ""
  for node in nodelist:
    if node.nodeType == node.TEXT_NODE:
      rc = rc + node.data
  return rc

#
# buildSOAPHeader
#
def buildSOAPHeader (creds) :
  header = """<UserCredentials xmlns="http://www.dre.vanderbilt.edu/CUTS">
      <Username>%s</Username>
      <Password>%s</Password>
    </UserCredentials>""" % (creds.username, creds.password)

  return header

#
# buildSOAPMessage
#
def buildSOAPMessage (creds, body) :
  # first, build the header for the SOAP message
  header = buildSOAPHeader (creds)

  # finally, build the complete SOAP message
  message = """<?xml version="1.0" encoding="UTF-8"?>
<SOAP-ENV:Envelope
  SOAP-ENV:encodingStyle="http://schemas.xmlsoap.org/soap/encoding/"
  xmlns:SOAP-ENC="http://schemas.xmlsoap.org/soap/encoding/"
  xmlns:xsi="http://www.w3.org/1999/XMLSchema-instance"
  xmlns:SOAP-ENV="http://schemas.xmlsoap.org/soap/envelope/">
  <SOAP-ENV:Header>%s</SOAP-ENV:Header>
  <SOAP-ENV:Body>%s</SOAP-ENV:Body>
</SOAP-ENV:Envelope>""" % (header, body)

  return message

#
# sendSOAPMessage
#
def sendSOAPMessage (server, creds, message, action) :
  # prepare the web service client
  message = buildSOAPMessage (creds, message)

  # construct a HTTP service object
  webservice = httplib.HTTP (server)

  # insert the headers into the message
  webservice.putrequest ("POST", "/CUTS/rmi/unittest.asmx HTTP/1.0")
  webservice.putheader ("Host", server)
  webservice.putheader ("User-Agent", "CUTS")
  webservice.putheader ("Content-type", "text/xml; charset=\"UTF-8\"")
  webservice.putheader ("Content-length", "%d" % len (message))
  webservice.putheader ("SOAPAction", '"http://www.dre.vanderbilt.edu/CUTS/' + action + '"')
  webservice.endheaders ()

  # send the message to the server and get its reply
  webservice.send (message)
  statuscode, statusmessage, header = webservice.getreply ()

  if (statuscode == 200):
    return xml.dom.minidom.parse (webservice.getfile ())

  print 'error:', statuscode, statusmessage
  return None

###############################################################################
## main entry point

if __name__ == "__main__":
  main ()
