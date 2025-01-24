using Newtonsoft.Json;

namespace factoryWork;

public class JsonFormatter : IFormatter
{
    public string Format(IBuilding building)
    {
        return JsonConvert.SerializeObject(building, Formatting.Indented);
    }
}