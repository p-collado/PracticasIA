local SLAXML = require 'slaxdom'

function translateAttr(xmlattr)
    if not xmlattr then
        return {}
    end
    attrs = {}
    for _, attr in ipairs(xmlattr) do
        attrs[attr.name] = attr.value
        attrs[#attrs+1] = attr.name
    end
    return attrs
end

function translateXML(xmltable)
    local trans = {}
    trans.tag = xmltable.name
    trans.attr = translateAttr(xmltable.attr)
    if xmltable.type == "element" then
        for _, child in ipairs(xmltable.kids) do
            trans[#trans+1] = translateXML(child)
        end
    elseif xmltable.type == "text" then
        return xmltable.value
    end
    return trans
end

function readXML(filename)
    local f = io.open(filename, "r")
    local content = f:read("*all")
    local xml_table = SLAXML:dom(content,{stripWhitespace=true})
    f:close()
    return translateXML(xml_table.root)
end

--function writeXML(xml_table, filename)
--    local xml_string = etree.tostring(xml_table)
--    local f = io.open(filename, "w")
--    print(xml_string)
--    f:write(xml_string)
--    f:close()
--end