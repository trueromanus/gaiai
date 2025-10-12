using GaiaiLogic;
using SkiaSharp;

GameLibrary.InitializeGame ( "en" );

string outputPath = "C:/work/Repositories/output_image.png";
CreateAndSaveImage ( outputPath, 500, 400, GameLibrary.GetHouses ().Take(16) );

/*GameLibrary.RunTimer ();

Thread.Sleep ( 100000 );*/



SKBitmap LoadShape ( string shape, Dictionary<string, SKBitmap> shapeCache ) {
    if ( shapeCache.ContainsKey ( shape ) ) return shapeCache[shape];

    using var stream = File.OpenRead ( $"C:/work/Repositories/HackingGame/game/gaiai/src/Images/houseshape.{shape}.png" );
    var originalBitmap = SKBitmap.Decode ( stream );
    shapeCache.Add ( shape, originalBitmap );
    return originalBitmap;
}

void CreateAndSaveImage ( string outputPath, int width, int height, IEnumerable<(string shape, int x, int y, int rotate)> houses ) {
    Dictionary<string, SKBitmap> shapeCache = new Dictionary<string, SKBitmap> ();

    using var bitmap = new SKBitmap ( new SKImageInfo ( width, height, SKColorType.Rgba8888, SKAlphaType.Premul ) );

    using var canvas = new SKCanvas ( bitmap );
    canvas.Clear ( SKColors.White );

    foreach ( var house in houses ) {
        var houseBitmap = LoadShape ( house.shape, shapeCache );

        canvas.Save ();

        var point = new SKPoint {
            X = house.x,
            Y = house.y,
        };
        canvas.Translate ( house.x + houseBitmap.Width / 2f, house.y + houseBitmap.Height / 2f );
        canvas.RotateDegrees ( house.rotate );
        canvas.Translate ( -houseBitmap.Width / 2f, -houseBitmap.Height / 2f );
        canvas.DrawBitmap ( houseBitmap, SKPoint.Empty );

        canvas.Restore ();
    }

    using var image = SKImage.FromBitmap ( bitmap );
    using var data = image.Encode ( SKEncodedImageFormat.Png, 100 ); // Encode as PNG with 100% quality
    using var stream = File.OpenWrite ( outputPath );
    data.SaveTo ( stream );
}