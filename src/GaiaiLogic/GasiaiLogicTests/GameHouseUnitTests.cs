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

    }

}
