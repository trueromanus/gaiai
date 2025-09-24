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
                                    var number = index + 1;
                                    var enabled = group.Triggers.Any ( b => b == number );
                                    return new GameHouseFuse {
                                        Number = index + 1,
                                        Correct = enabled,
                                        Enabled = enabled
                                    };
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
                var values = group.Triggers.Values;
                var allCorrectEnabled = values.Where ( a => a.Correct ).All ( a => a.Enabled );
                var allNotCorrectDisabled = values.Where ( a => !a.Correct ).All ( a => !a.Enabled );
                if ( !( allCorrectEnabled && allNotCorrectDisabled ) ) {
                    notCorrectLevels++;
                }
            }

            return notCorrectLevels;
        }

        public void ToggleTrigger ( int line, int fuse ) {
            if ( line >= FusesGroups.Count ) return;
            var group = FusesGroups[line];

            var fuseItem = group.Triggers.Values.FirstOrDefault ( a => a.Number == fuse );
            if ( fuseItem == null ) return;

            fuseItem.Enabled = !fuseItem.Enabled;
        }

        public void RestoreToCorrect () {
            foreach ( var group in FusesGroups ) {
                foreach ( var trigger in group.Triggers.Values ) {
                    trigger.Enabled = trigger.Correct ? true : false;
                }
            }
        }

    }

}
