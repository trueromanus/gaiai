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
                        Triggers = Enumerable.Repeat ( new GameHouseFuse (), group.Width )
                            .Select (
                                ( a, index ) => {
                                    a.Number = index + 1;
                                    a.Enabled = group.Triggers.Any ( b => b == a.Number );
                                    a.Correct = a.Enabled;
                                    return a;
                                }
                            )
                            .ToDictionary ( a => a.Number )
                    }
                )
                .ToList ();
        }

        public int NotCorrectLevel () {
            if ( !FusesGroups.Any () ) return 0;

            var notCorrectLevels = 0;

            foreach ( var group in FusesGroups ) {
                if ( group.Triggers.Values.All ( a => a.Enabled && a.Correct ) ) {
                    notCorrectLevels++;
                }
            }

            return notCorrectLevels;
        }

    }

}
