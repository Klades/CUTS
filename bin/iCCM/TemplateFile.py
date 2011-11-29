# -*- Python -*-

#
# @class TemplateFile
#
# Utility class for generate files from templates. This extends
# the basic functionality of templates such that a template file
# can have more complex template expressions.
#
class TemplateDirectory :
  #
  # Evaluate all the templates in this directory, including its
  # subdirectorys. The template extension is removed from the
  # template file.
  #
  def evaluate (self, dir, locals, gendir) :
    import os
    from os.path import join, relpath, exists
    
    for root, dirs, files in os.walk (dir):
      for name in files:
        # Make sure the file is actually a template file. Template
        # files end with the .tmpl extension.
        def is_template_file (filename):
          return os.path.splitext (filename)[1] == '.tmpl'
          
        if not is_template_file (name):
          continue
        
        template_file = join (root, name) 
        target_dir = join (gendir, relpath (root, dir))
        
        # Make sure the target directory exists.
        if not exists (target_dir):
          os.makedirs (target_dir)
          
        def get_basename (template):
          return template[0:len (template) - 4]
          
        # Open the target file for writing. Right now, we are cheating
        # when it comes to constructing the file basename. In the
        # future, we would like to allow the filename to be configured
        # via the template, or the command-line.
        basename = locals['arch_name'] + '_' + get_basename (name)
        target_filename = join (target_dir, basename)
        target_file = open (target_filename, "w")
        
        # Evaluate the template by writing the expanded contents to
        # the target output file.
        tf = TemplateFile (template_file)
        tf.evaluate (target_file, locals)
        
        # Close the output file.
        target_file.close ()

#
# @class TemplateFile
#
# Utility class for generate files from templates. This extends
# the basic functionality of templates such that a template file
# can have more complex template expressions.
#
class TemplateFile:
  #
  # Default constructor
  #
  def __init__ (self):
    self._template = None
  
  #
  # Constructor. Open the template file for reading during the
  # constuction process.
  #
  # @param          filename          Template filename
  # 
  def __init__ (self, filename):
    self.open (filename)
    
  #
  # Open the template file for processing
  #
  # @param          template        Template file to read
  def open (self, template):
    self._template = open (template, "r")
    
  #
  # Evaluate the template file using the local parameters. Each
  # parameters in the template is replaced with a concrete value.
  # If a parameter is not located in the locals, then an exception
  # is raised.
  #
  # @param          target          Target file object
  # @param          locals          Concrete values
  #
  def evaluate (self, target, locals): 
    for line in self._template:
      self._evaluate_line (target, line, locals)
        
  #
  # Close the template file.
  #
  def close ():
    self._template.close ()
    
  #
  # Helper function that evaluates each line in the template.
  #
  def _evaluate_line (self, target, line, locals):
    import re
    
    pattern = '(?P<pre>[^$]*)(?:(?:\$\{(?P<expr>[^}]+)\}|(?:\$(?P<escape>\$))))?'
    for match in re.finditer (pattern, line) :
      if match.group ('pre') != None:
        target.write (match.group ('pre'))
      
      if match.group ('expr') != None:
        str = eval (match.group ('expr'), {}, locals)
        target.write (str)
        
      if match.group ('escape') != None:
        target.write ('$')
    