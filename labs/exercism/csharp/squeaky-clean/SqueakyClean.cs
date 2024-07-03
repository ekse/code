using System;
using System.Text;

public static class Identifier
{
    public static string Clean(string identifier)
    {
        StringBuilder builder = new StringBuilder();
        bool capitalizeNextLetter = false;

        foreach (char c in identifier)
        {
            if (capitalizeNextLetter)
            {
                builder.Append(char.ToUpper(c));
                capitalizeNextLetter = false;
                continue;
            }

            if (c == '-')
            {
                capitalizeNextLetter = true;
                continue;
            }

            if (char.IsWhiteSpace(c))
            {
                builder.Append('_');
                continue;
            }

            if (char.IsControl(c))
            {
                builder.Append("CTRL");
                continue;
            }

            if (!char.IsLetter(c))
            {
                continue;                
            }

            if (c >= 'α' && c <= 'ω')
            {
                continue;
            }

            builder.Append(c);
        }

        return builder.ToString();
    }
}
