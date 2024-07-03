using System;

public struct CurrencyAmount
{
    private decimal amount;
    private string currency;

    public CurrencyAmount(decimal amount, string currency)
    {
        this.amount = amount;
        this.currency = currency;
    }

    public static bool operator ==(CurrencyAmount a, CurrencyAmount b)
    {
        if (a.currency != b.currency) 
            throw new ArgumentException();
        
        return a.amount == b.amount;

    }

    public static bool operator !=(CurrencyAmount a, CurrencyAmount b)
    {
        return !(a == b);
    }

    public static bool operator >(CurrencyAmount a, CurrencyAmount b)
    {
        if (a.currency != b.currency)
            throw new ArgumentException();

        return a.amount > b.amount;
    }

    public static bool operator <(CurrencyAmount a, CurrencyAmount b)
    {
        if (a.currency != b.currency)
            throw new ArgumentException();

        return a.amount < b.amount;
    }

    public static decimal operator +(CurrencyAmount a, CurrencyAmount b)
    {
        if (a.currency != b.currency)
            throw new ArgumentException();

        return a.amount + b.amount;
    }

    public static decimal operator -(CurrencyAmount a, CurrencyAmount b)
    {
        if (a.currency != b.currency)
            throw new ArgumentException();

        return a.amount - b.amount;
    }

    public static explicit operator double(CurrencyAmount a)
    {
        return (double) a.amount;
    }

    public static implicit operator decimal(CurrencyAmount a)
    {
        return a.amount;
    }

}
