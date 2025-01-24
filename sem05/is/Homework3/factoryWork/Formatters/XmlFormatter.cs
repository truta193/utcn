namespace factoryWork;
using System;
using System.IO;
using System.Xml.Serialization;

public class XmlFormatter : IFormatter
{
    public string Format(IBuilding building)
    {
        var serializer = new XmlSerializer(building.GetType());
        
        using (var stringWriter = new StringWriter())
        {
            serializer.Serialize(stringWriter, building);
            return stringWriter.ToString();
        }
    }
}

