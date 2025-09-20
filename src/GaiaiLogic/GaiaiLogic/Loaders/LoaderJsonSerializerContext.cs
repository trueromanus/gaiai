using GaiaiLogic.Models;
using System.Text.Json.Serialization;

namespace GaiaiLogic.Loaders {


    [JsonSerializable ( typeof ( IEnumerable<LampPost> ) )]
    [JsonSerializable ( typeof ( IEnumerable<TrafficLight> ) )]
    [JsonSourceGenerationOptions ( PropertyNamingPolicy = JsonKnownNamingPolicy.CamelCase )]
    internal partial class LoaderJsonSerializerContext : JsonSerializerContext {
    }

}
