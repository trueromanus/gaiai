using GaiaiLogic.Interactive;
using GaiaiLogic.Models;

namespace GaiaiLogicTests {

    public class GameHouseUnitTests {

        [Fact]
        public void NotCorrectLevel_Completed_Case1 () {
            // arrange
            var house = new GameHouse (
                new House {
                    Fuses = new List<HouseFuse> {
                        new HouseFuse {
                            Width = 5,
                            Triggers = [1,3,5]
                        }
                    }
                }
            );

            // act
            var level = house.NotCorrectLevel ();

            // assert
            Assert.Equal ( 0, level );
        }

        [Fact]
        public void NotCorrectLevel_Completed_Case2 () {
            // arrange
            var house = new GameHouse (
                new House {
                    Fuses = new List<HouseFuse> {
                        new HouseFuse {
                            Width = 5,
                            Triggers = [1,5]
                        }
                    }
                }
            );
            house.ToggleTrigger ( 0, 1 );

            // act
            var level = house.NotCorrectLevel ();

            // assert
            Assert.Equal ( 1, level );
        }

        [Fact]
        public void NotCorrectLevel_Completed_Case3 () {
            // arrange
            var house = new GameHouse (
                new House {
                    Fuses = new List<HouseFuse> {
                        new HouseFuse {
                            Width = 5,
                            Triggers = [1,5]
                        },
                        new HouseFuse {
                            Width = 2,
                            Triggers = [2]
                        }
                    }
                }
            );
            house.ToggleTrigger ( 0, 1 );
            house.ToggleTrigger ( 1, 2 );

            // act
            var level = house.NotCorrectLevel ();

            // assert
            Assert.Equal ( 2, level );
        }

        [Fact]
        public void RestoreToCorrect_Completed_Case1 () {
            // arrange
            var house = new GameHouse (
                new House {
                    Fuses = new List<HouseFuse> {
                        new HouseFuse {
                            Width = 5,
                            Triggers = [1,2,5]
                        },
                        new HouseFuse {
                            Width = 2,
                            Triggers = [2]
                        },
                        new HouseFuse {
                            Width = 3,
                            Triggers = [1,3]
                        }
                    }
                }
            );
            house.ToggleTrigger ( 0, 1 );
            house.ToggleTrigger ( 0, 2 );
            house.ToggleTrigger ( 0, 3 );
            house.ToggleTrigger ( 0, 4 );
            house.ToggleTrigger ( 0, 5 );

            house.ToggleTrigger ( 1, 1 );
            house.ToggleTrigger ( 1, 2 );

            house.ToggleTrigger ( 2, 1 );
            house.ToggleTrigger ( 2, 2 );
            house.ToggleTrigger ( 2, 3 );
            var initialLevel = house.NotCorrectLevel ();

            // act
            house.RestoreToCorrect ();

            // assert
            Assert.Equal ( 3, initialLevel );
            Assert.Equal ( 0, house.NotCorrectLevel () );
        }

    }

}
