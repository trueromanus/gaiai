using GaiaiLogic.Models;
using System.Text.Json.Serialization;

namespace GaiaiLogic.Loaders {


    [JsonSerializable ( typeof ( IEnumerable<LampPost> ) )]
    [JsonSerializable ( typeof ( IEnumerable<TrafficLight> ) )]
    [JsonSerializable ( typeof ( IEnumerable<House> ) )]
    [JsonSourceGenerationOptions ( PropertyNamingPolicy = JsonKnownNamingPolicy.CamelCase )]
    internal partial class LoaderJsonSerializerContext : JsonSerializerContext {
    }

}
