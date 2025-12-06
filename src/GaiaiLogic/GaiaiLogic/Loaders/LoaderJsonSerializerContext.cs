using GaiaiLogic.Models;
using System.Text.Json.Serialization;

namespace GaiaiLogic.Loaders {


    [JsonSerializable ( typeof ( IEnumerable<LampPost> ) )]
    [JsonSerializable ( typeof ( IEnumerable<TrafficLight> ) )]
    [JsonSerializable ( typeof ( IEnumerable<House> ) )]
    [JsonSerializable ( typeof ( IEnumerable<Road> ) )]
    [JsonSourceGenerationOptions ( PropertyNamingPolicy = JsonKnownNamingPolicy.CamelCase )]
    internal partial class LoaderJsonSerializerContext : JsonSerializerContext {
    }

}
