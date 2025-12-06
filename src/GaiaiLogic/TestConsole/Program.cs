using GaiaiLogic;
using Raylib_cs;
using System.Numerics;

namespace RayLibExperiment {

    public static class Program {

        [STAThread]
        public static void Main () {
            GameLibrary.InitializeGame ( "en" );

            Raylib.InitWindow ( 800, 480, "Hello World" );
            Raylib.SetTargetFPS ( 60 );

            var image = Raylib.LoadImage ( $"C:/work/Repositories/HackingGame/game/gaiai/src/Images/houseshape.simplerect.png" );
            Texture2D texture = Raylib.LoadTextureFromImage ( image );
            Raylib.UnloadImage ( image );
            var houses = GameLibrary.GetHouses ();
            var trafficLights = GameLibrary.GetTrafficeLights().Take ( 1 ).ToList ();
            var roads = GameLibrary.GetRoads ( "south" );

            while ( !Raylib.WindowShouldClose () ) {
                Raylib.BeginDrawing ();
                Raylib.ClearBackground ( Color.White );

                foreach ( var house in houses ) {
                    Rectangle sourceRec = new Rectangle ( 0.0f, 0.0f, texture.Width, texture.Height );
                    Rectangle destRec = new Rectangle ( house.x, house.y, texture.Width, texture.Height );
                    Vector2 origin = new Vector2 ( destRec.Width / 2.0f, destRec.Height / 2.0f );

                    Raylib.DrawTexturePro ( texture, sourceRec, destRec, origin, house.rotate, Color.White );
                }

                foreach ( var trafficLight in trafficLights ) {
                    Raylib.DrawCircle ( trafficLight.x, trafficLight.y, 4, Color.Black );
                }

                foreach ( var road in roads ) {
                    Raylib.DrawLineEx ( road.start, road.finish, 2, Color.Orange );
                }

                Raylib.EndDrawing ();
            }

            Raylib.CloseWindow ();
        }

    }

}