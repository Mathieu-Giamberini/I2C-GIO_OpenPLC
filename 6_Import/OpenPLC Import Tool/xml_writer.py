from function_block import FunctionBlock, Variable

def update_definitions(lib_name, definitions_file):
    if lib_name in definitions_file:
        #lib already exists in definitions file
        return definitions_file
    
    lines = definitions_file.split('\n')
    definitions_file = ''
    found_libs_var = False
    for line in lines:
        if 'StdTC6Libs' in line:
            found_libs_var = True
        
        #Search for the end of libs_var declaration
        if found_libs_var and '))]' in line:
            lib_name_xml = lib_name.replace(' ', '_') + '.xml'
            new_lib_declaration = ''')),
              (_("''' + lib_name + '"), join(sd, "' + lib_name_xml + '"))]'
            line = line.replace('))]', new_lib_declaration)
            found_libs_var = False
        
        definitions_file += line + '\n'
    
    return definitions_file

def create_blank_xml(lib_name):
    xml_header = """<?xml version='1.0' encoding='utf-8'?>
<project xmlns:ns1="http://www.plcopen.org/xml/tc6_0201" xmlns:xhtml="http://www.w3.org/1999/xhtml" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns="http://www.plcopen.org/xml/tc6_0201">
<fileHeader companyName="OpenPLC" productName=""" + '"' + lib_name + '"' + """ productVersion="1.0" creationDateTime="2023-04-26T04:54:00"/>
<contentHeader name=""" + '"' + lib_name + '"' + """ author="OpenPLC Lib Writter" modificationDateTime="2023-04-26T04:54:00">
<coordinateInfo>
<fbd>
<scaling x="0" y="0"/>
</fbd>
<ld>
<scaling x="0" y="0"/>
</ld>
<sfc>
<scaling x="0" y="0"/>
</sfc>
</coordinateInfo>
</contentHeader>
<types>
<dataTypes/>
<pous>
</pous>
</types>
<instances>
<configurations/>
</instances>
</project>"""
    return xml_header

def generate_vars(var_block):
    return_str = ''
    for variable in var_block:
        if variable.type == 'STRING':
            variable.type == 'string'
        return_str += '<variable name="' + variable.name + '">\n<type>\n<' + variable.type + '/>\n</type>\n'
        return_str += '<documentation>\n<xhtml:p><![CDATA[' + variable.name + ']]></xhtml:p>\n</documentation>\n</variable>\n'
    
    return return_str



def generate_xml(lib_name, function_blocks, xml_file):
    if xml_file is None:
        xml_file = create_blank_xml(lib_name)
    
    xml_pous = ''
    for fb in function_blocks:
        if fb.type == "FunctionBlock":
            xml_pous += '<pou name="' + fb.name + '" pouType="functionBlock">\n<interface>\n'
        else:
            xml_pous += '<pou name="' + fb.name + '" pouType="function">\n<interface>\n<returnType>\n'
            xml_pous += '<' + fb.type + '/>\n</returnType>\n'

        if len(fb.inputs) > 0:
            xml_pous += '<inputVars>\n'
            xml_pous += generate_vars(fb.inputs)
            xml_pous += '</inputVars>\n'
        if len(fb.locals) > 0:
            xml_pous += '<localVars>\n'
            xml_pous += generate_vars(fb.locals)
            xml_pous += '</localVars>\n'
        if len(fb.outputs) > 0:
            xml_pous += '<outputVars>\n'
            xml_pous += generate_vars(fb.outputs)
            xml_pous += '</outputVars>\n'

        xml_pous += '</interface>\n<body>\n<ST>\n<xhtml:p><![CDATA['
        xml_pous += fb.code + ']]></xhtml:p>'
        xml_pous += """</ST>
</body>
<documentation>
<xhtml:p><![CDATA["""
        xml_pous += fb.name + """]]></xhtml:p>
</documentation>
</pou>"""
        
    xml_pous += '\n</pous>'

    generated_output = ''
    lines = xml_file.split('\n')
    for line in lines:
        if '</pous>' in line:
            generated_output += xml_pous + '\n'
        else:
            generated_output += line + '\n'

    return generated_output


def generate_plc_project(proj_name, function_blocks):
    beremiz_file = """<?xml version='1.0' encoding='utf-8'?>
<BeremizRoot xmlns:xsd="http://www.w3.org/2001/XMLSchema" URI_location="LOCAL://">
  <TargetType/>
</BeremizRoot>"""
    plc_file = """<?xml version='1.0' encoding='utf-8'?>
<project xmlns:ns1="http://www.plcopen.org/xml/tc6.xsd" xmlns:xhtml="http://www.w3.org/1999/xhtml" xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns="http://www.plcopen.org/xml/tc6_0201">
  <fileHeader companyName="Unknown" productName="Unnamed" productVersion="1" creationDateTime="2022-08-16T15:49:17"/>
  <contentHeader name="Unnamed" modificationDateTime="2023-06-13T16:55:33">
    <coordinateInfo>
      <fbd>
        <scaling x="10" y="10"/>
      </fbd>
      <ld>
        <scaling x="10" y="10"/>
      </ld>
      <sfc>
        <scaling x="10" y="10"/>
      </sfc>
    </coordinateInfo>
  </contentHeader>
  <types>
    <dataTypes/>
    <pous>
      <pou name="program0" pouType="program">
        <interface>
          <localVars>
            <variable name="dummy_var">
              <type>
                <BOOL/>
              </type>
            </variable>
          </localVars>
        </interface>
        <body>
          <ST>
            <xhtml:p><![CDATA[dummy_var := 1;]]></xhtml:p>
          </ST>
        </body>
      </pou>
    </pous>
  </types>
  <instances>
    <configurations>
      <configuration name="Config0">
        <resource name="Res0">
          <task name="task0" priority="0" interval="T#20ms">
            <pouInstance name="instance0" typeName="program0"/>
          </task>
        </resource>
      </configuration>
    </configurations>
  </instances>
</project>
    """

    plc_file = generate_xml(proj_name, function_blocks, plc_file)

    return beremiz_file, plc_file

    