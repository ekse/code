using System;
using System.Collections.Generic;



public class FacialFeatures : IEquatable<FacialFeatures>
{
    public string EyeColor { get; }
    public decimal PhiltrumWidth { get; }

    public FacialFeatures(string eyeColor, decimal philtrumWidth)
    {
        EyeColor = eyeColor;
        PhiltrumWidth = philtrumWidth;
    }



    public override bool Equals(object obj)

        => obj is FacialFeatures features &&

            Equals(features);



    public override int GetHashCode()

        => HashCode.Combine(EyeColor, PhiltrumWidth);



    public bool Equals(FacialFeatures other)

        => EyeColor == other.EyeColor &&

            PhiltrumWidth == other.PhiltrumWidth;

}

public class Identity : IEquatable<Identity>
{
    public string Email { get; }
    public FacialFeatures FacialFeatures { get; }

    public Identity(string email, FacialFeatures facialFeatures)
    {
        Email = email;
        FacialFeatures = facialFeatures;
    }



    public override bool Equals(object obj)

        => obj is Identity identity &&

            Equals(identity);



    public override int GetHashCode()

        => HashCode.Combine(Email, FacialFeatures);



    public bool Equals(Identity other)

       => Email == other.Email &&

           EqualityComparer<FacialFeatures>.Default.Equals(FacialFeatures, other.FacialFeatures);

}

public class Authenticator
{
    HashSet<Identity> _registeredIdentities = new();
    public static bool AreSameFace(FacialFeatures faceA, FacialFeatures faceB)
        => faceA.Equals(faceB);

    public bool IsAdmin(Identity identity)
        => identity.Equals(new Identity("admin@exerc.ism", new FacialFeatures("green", 0.9M)));

    public bool Register(Identity identity)

        => _registeredIdentities.Add(identity);


    public bool IsRegistered(Identity identity)
        => _registeredIdentities.Contains(identity);

    public static bool AreSameObject(Identity identityA, Identity identityB)
        => ReferenceEquals(identityA, identityB);
}
