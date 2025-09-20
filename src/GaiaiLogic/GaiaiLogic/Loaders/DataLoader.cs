using GaiaiLogic.Models;
using System.Reflection;
using System.Text.Json;

namespace GaiaiLogic.Loaders {

    internal class DataLoader {

        private Assembly? m_assembly;

        public DataLoader () => m_assembly = typeof ( DataLoader ).Assembly;

        public IEnumerable<LampPost> LoadLampPosts () {
            var items = JsonSerializer.Deserialize ( GetResourceStream ( "" ), typeof ( IEnumerable<LampPost> ), LoaderJsonSerializerContext.Default );
            if ( items == null ) throw new Exception ( "Can't deserialize LampPosts!" );

            var result = items as IEnumerable<LampPost>;
            if ( result == null ) throw new Exception ( "Can't conversion LampPosts!" );

            return result;
        }

        public IEnumerable<TrafficLight> LoadTrafficLights() {
            var items = JsonSerializer.Deserialize ( GetResourceStream ( "" ), typeof ( IEnumerable<TrafficLight> ), LoaderJsonSerializerContext.Default );
            if ( items == null ) throw new Exception ( "Can't deserialize TrafficLight!" );

            var result = items as IEnumerable<TrafficLight>;
            if ( result == null ) throw new Exception ( "Can't conversion TrafficLight!" );

            return result;
        }

        private Stream GetResourceStream ( string file ) {
            var stream = m_assembly!.GetManifestResourceStream ( file );
            if ( stream == null ) throw new Exception ( $"Can't read file {file} from resource!" );

            return stream;
        }

    }

}
