using GaiaiLogic.Interactive;
using GaiaiLogic.Models;

namespace GaiaiLogicTests {

    public class GameCitizenUnitTests {

        [Fact]
        public void IncreaseCraziness_Completed_Default () {

            // arrange
            // act
            var citizen = new GameCitizen ( "arg1", "title", new List<CitizenSchedule> () );

            //assert
            Assert.Equal ( 0, citizen.Craziness );
        }

        [Fact]
        public void IncreaseCraziness_Completed_Increase_Case1 () {

            // arrange
            var citizen = new GameCitizen ( "arg1", "title", new List<CitizenSchedule> () );

            // act
            citizen.IncreaseCraziness ( 10 );

            //assert
            Assert.Equal ( 10, citizen.Craziness );
        }

        [Fact]
        public void IncreaseCraziness_Completed_Increase_Case2 () {

            // arrange
            var citizen = new GameCitizen ( "arg1", "title", new List<CitizenSchedule> () );
            citizen.IncreaseCraziness ( 50 );

            // act
            citizen.IncreaseCraziness ( 60 );

            //assert
            Assert.Equal ( 100, citizen.Craziness );
        }

    }

}
