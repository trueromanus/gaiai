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

    }

}
