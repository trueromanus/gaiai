using GaiaiLogic.Models;

namespace GaiaiLogic.Interactive {

    internal class GameHouse {

        public string Name { get; internal set; }

        public string Shape { get; internal set; }

        public GamePosition Position { get; internal set; }

        public List<GameHouseFuseGroup> FusesGroups { get; internal set; } = new List<GameHouseFuseGroup> ();

        public GameHouse ( House house ) {
            Name = house.Name;
            Shape = house.Shape;
            Position = new GamePosition ( house.X, house.Y, house.Rotation );
            if ( !house.Fuses.Any () ) return;

            FusesGroups = house.Fuses
                .Select (
                    group => new GameHouseFuseGroup {
                        Width = group.Width,
                        Triggers = group.Triggers
                            .Select (
                                a => new GameHouseFuse {
                                    Enabled = true,
                                    Number = a
                                }
                            )
                            .ToDictionary ( a => a.Number )
                    }
                )
                .ToList ();
        }

    }

}
