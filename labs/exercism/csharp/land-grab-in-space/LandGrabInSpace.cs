using System;
using System.Collections.Generic;
using System.Linq;

public struct Coord
{
    public Coord(ushort x, ushort y)
    {
        X = x;
        Y = y;
    }

    public ushort X { get; }
    public ushort Y { get; }
}

public struct Plot
{
    public Coord a { get; }
    public Coord b { get; }
    public Coord c { get; }
    public Coord d { get; }

    public Plot(Coord a, Coord b, Coord c, Coord d)
    {
        this.a = a;
        this.b = b;
        this.c = c;
        this.d = d;
    }
}

public class ClaimsHandler
{
    List<Plot> claims = [];

    public void StakeClaim(Plot plot) => claims.Add(plot);

    public bool IsClaimStaked(Plot plot) => claims.Contains(plot);

    public bool IsLastClaim(Plot plot) => claims.Last().Equals(plot);

    // d=√((x_2-x_1)²+(y_2-y_1)²)
    private double DistanceBetweenPoints(Coord a, Coord b)
    {
        return Math.Sqrt(Math.Pow((a.X - b.X), 2) + Math.Pow((a.Y - b.Y), 2));
    }

    public Plot GetClaimWithLongestSide()
    {
        double longestSide = -1;
        Plot plotWithLongestSide = claims[0];

        foreach (Plot plot in claims)
        {
            List<double> distances = [ 
                DistanceBetweenPoints(plot.a, plot.b), 
                DistanceBetweenPoints(plot.b, plot.c), 
                DistanceBetweenPoints(plot.c, plot.d), 
                DistanceBetweenPoints(plot.d, plot.a) ];
            
            double longest = distances.Max();

            if (longest > longestSide)
            {
                longestSide = longest;
                plotWithLongestSide = plot;
            }
        }

        return plotWithLongestSide;
    }
}
