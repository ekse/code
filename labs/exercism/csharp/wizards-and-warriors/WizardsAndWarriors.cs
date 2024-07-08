using System;

abstract class Character
{
    private readonly string _characterType;
    protected bool _vulnerable = false;

    protected Character(string characterType)
    {
        _characterType = characterType;
    }

    public abstract int DamagePoints(Character target);

    public virtual bool Vulnerable()
    {
        return _vulnerable;
    }

    public override string ToString()
    {
        return $"Character is a {_characterType}";
    }
}

class Warrior : Character
{
    public Warrior() : base("Warrior")
    {
    }

    public override int DamagePoints(Character target) => target.Vulnerable() ? 10 : 6;
}

class Wizard : Character
{

    private bool _hasPreparedSpell = false;

    public Wizard() : base("Wizard")
    {
        base._vulnerable = true;
    }

    public override int DamagePoints(Character target)
    {
        if (_hasPreparedSpell)
        {
            _hasPreparedSpell = false;
            return 12;
        }

        return 3;
    }

    public void PrepareSpell()
    {
        _hasPreparedSpell = true;
        base._vulnerable = false;
    }
}
