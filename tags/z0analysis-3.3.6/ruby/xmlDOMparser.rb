#!/usr/bin/ruby -w

# http://www.tutorialspoint.com/ruby/ruby_xml_xslt.htm

=begin

require 'rexml/document'
include REXML

xmlfile = File.new("../xml/cutflow.xml")
xmldoc = Document.new(xmlfile)

# Now get the root element
root = xmldoc.root
#puts "Root element : " + root.attributes[""]

# This will output all the movie titles.
xmldoc.elements.each("objects/obj"){ 
   |e| puts "NAME : " + e.attributes["NMAE"] 
}

# This will output all the movie types.
xmldoc.elements.each("objects/obj/phase") {
   |e| puts "phase : " + e.text 
}

# This will output all the movie description.
xmldoc.elements.each("objects/obj/description") {
   |e| puts "Description : " + e.text 
}

=end


=begin
require 'rexml/document'
include REXML

xmlfile = File.new("../xml/cutflow.xml")
xmldoc = Document.new(xmlfile)

# Info for the first movie found
movie = XPath.first(xmldoc, "//obj")
p movie

# Print out all the movie types
XPath.each(xmldoc, "//phase") { |e| puts e.text }

# Get an array of all of the movie formats.
names = XPath.match(xmldoc, "//parameters").map {|x| x.text }
p names
=end



=begin
require 'rexml/document'                                             
    include REXML
    
    def compact(node,indent)                                             
      if(node.class==Element)                                            
        print node.name+"["
        indent += ' '*(node.name.length+1);
        first=true;
        node.attributes.each do |key,value|                              
          print "\n#{indent}" unless first
          print "@#{key}[#{value}]"
          first=false;
        end
        node.children.each do |child|                                    
       # deal only with element nodes or non-"empty" text nodes 
          if child.class==Element || child.value.strip.length>0          
            print "\n#{indent}" unless first
            compact(child,indent)
            first=false;
       end
        end
        print "]"
      elsif node.class==Text                                             
        print node.value.strip.gsub(/ *\n */," ") # normalize new lines
   end
    end
    
#    doc = Document.new(STDIN)                                            
#    compact(doc.root,"")
    compact("../xml/cutflow.xml","")
=end


# http://xml-simple.rubyforge.org/

