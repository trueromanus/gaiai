using GaiaiLogic.Models;
using System.Numerics;

namespace GaiaiLogic.Interactive {

    internal class GameRoad {

        public Vector2 Start { get; internal set; }

        public Vector2 Finish { get; internal set; }

        public GameRoad (Road road) {
            Start = new Vector2 ( road.X1, road.Y1 );
            Finish = new Vector2 ( road.X2, road.Y2 );
        }

    }

}
