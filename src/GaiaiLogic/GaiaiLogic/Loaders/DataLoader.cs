using GaiaiLogic.Models;
using System.Reflection;
using System.Text.Json;

namespace GaiaiLogic.Loaders {

    internal class DataLoader {

        private Assembly? m_assembly;

        public DataLoader () => m_assembly = typeof ( DataLoader ).Assembly;

        public void LoadStaticItems () {
            var lampPosts = LoadStaticItems<LampPost> ( "LampPosts", "LampPosts.json" );
            var trafficLights = LoadStaticItems<TrafficLight> ( "TrafficLights", "TrafficLights.json" );
            var houses = LoadStaticItems<House> ( "Houses", "Houses.json" );
        }

        private IEnumerable<T> LoadStaticItems<T> ( string name, string fileName ) {
            var items = JsonSerializer.Deserialize ( GetResourceStream ( "" ), typeof ( IEnumerable<T> ), LoaderJsonSerializerContext.Default );
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
