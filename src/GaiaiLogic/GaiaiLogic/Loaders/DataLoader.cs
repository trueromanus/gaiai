using GaiaiLogic.Models;
using System.Reflection;
using System.Text.Json;

namespace GaiaiLogic.Loaders {

    internal class DataLoader {

        private Assembly? m_assembly;

        public DataLoader () => m_assembly = typeof ( DataLoader ).Assembly;

        public LoadedStaticItems LoadStaticItems ( string language ) {
            var lampPosts = LoadStaticItems<LampPost> ( "LampPosts", $"LampPosts-{language}.json" );
            var trafficLights = LoadStaticItems<TrafficLight> ( "TrafficLights", $"TrafficLights-{language}.json" );
            var houses = LoadStaticItems<House> ( "Houses", $"Houses-{language}.json" );

            return new LoadedStaticItems {
                LampPosts = lampPosts,
                TrafficLights = trafficLights,
                Houses = houses
            };
        }

        private IEnumerable<T> LoadStaticItems<T> ( string name, string fileName ) {
            var items = JsonSerializer.Deserialize ( GetResourceStream ( fileName ), typeof ( IEnumerable<T> ), LoaderJsonSerializerContext.Default );
            if ( items == null ) throw new Exception ( "Can't deserialize LampPosts!" );

            var result = items as IEnumerable<T>;
            if ( result == null ) throw new Exception ( "Can't conversion LampPosts!" );

            return result;
        }

        private Stream GetResourceStream ( string file ) {
            var stream = m_assembly!.GetManifestResourceStream ( file );
            if ( stream == null ) throw new Exception ( $"Can't read file {file} from resource!" );

            return stream;
        }

    }

}
