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

#
# main
#
def main ():
  try:
    short_opt = "hlup:"
    long_opt = ["help", "server=", "test-suite=",
                "list-attributes", "update-attributes",
                "attribute-path=", "owner=",
                "interface-basename="]

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
  
  # parse the command-line arguments
  for o, a in opts:
    if o == "-v":
      verbose = True
    elif o in ("-h", "--help"):
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
    elif o in ("--owner"):
      owner = a
    else:
      assert False, "unhandled option"

  if list:
    list_attributes (server, suite)

  if update:
    attributes = update_attributes (path, owner, server, suite)
    write_interface_file (interface_basename, owner, attributes)

#
# list_attributes
#
def list_attributes (server, suite):
  attributes = get_output_attributes (server, suite)

  # print the only input attribute
  print " input attribute : CUTS.test.uuid"
 
  for attr in attributes:
    print "output attribute : %s" % attr

#
# write_interface_file
#
def write_interface_file (basename, owner, outputs):
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
  
  for attr in outputs:
    f.write ("  <output>%s</output>\n" % attr)

  f.write ("</interface>\n")

  # close the file
  f.close ()
  
#
# update_attributes
#
def update_attributes (path, owner, server, suite):
  attributes = get_output_attributes (server, suite)
  uuid = read_test_uuid (path)
  
  for attr in attributes:
    write_output_attribute (path, owner, server, uuid, attr)
    
  return attributes

#
# write_output_attribute
#
def write_output_attribute (path, owner, server, uuid, attr):
  print "writing attribute %s for test %s" % (attr, uuid)

  # construct the message for the request
  message = "UUID=%s&UnitTest=%s" % (uuid, attr)
   
  # prepare the web service client
  webservice = httplib.HTTP (server)
  webservice.putrequest ("POST", "/CUTS/Service.asmx/EvaluateUnitTest")
  webservice.putheader ("Host", server)
  webservice.putheader ("Content-Type", "application/x-www-form-urlencoded")
  webservice.putheader ("Content-Length", "%d" % len (message))
  webservice.endheaders ()
  
  # send the message to the server
  webservice.send (message)
  
  # get the reply
  statuscode, statusmessage, header = webservice.getreply ()

  if (statuscode == 200):
    # convert the response into an XML document
    response = xml.dom.minidom.parse (webservice.getfile ());
    values = response.getElementsByTagName ("string")

    # get the value from the response
    value = get_text (values[0].childNodes)
    
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
    # print the headers for the response
    print statuscode, statusmessage

#
# get_output_attributes
#
def get_output_attributes (server, suite):
  attrs = []

  # construct the message for the request
  message = "TestSuite=" + suite

  # construct and send the header
  webservice = httplib.HTTP (server)
  webservice.putrequest ("POST", "/CUTS/Service.asmx/ListUnitTests")
  webservice.putheader ("Host", server)
  webservice.putheader ("Content-Type", "application/x-www-form-urlencoded")
  webservice.putheader ("Content-Length", "%d" % len (message))
  webservice.endheaders ()

  # send the message to the server
  webservice.send (message)

  # get the response
  statuscode, statusmessage, header = webservice.getreply ()

  if (statuscode == 200):
    response = xml.dom.minidom.parse (webservice.getfile ());
    attributes = response.getElementsByTagName ("string")

    for attr in attributes:
      attrs.append (get_text (attr.childNodes))

  else:
    # print the headers for the response
    print statuscode, statusmessage

  return attrs

#
# read_test_uuid
#
def read_test_uuid (path):
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
  uuid = get_text (values[0].childNodes)
  return uuid  
  
#
# get_text
#
def get_text (nodelist):
  rc = ""
  for node in nodelist:
    if node.nodeType == node.TEXT_NODE:
      rc = rc + node.data
  return rc

###############################################################################
## main entry point

if __name__ == "__main__":
  main ()
