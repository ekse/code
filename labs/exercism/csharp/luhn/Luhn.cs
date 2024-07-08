public static class Luhn
{
    public static bool IsValid(string number)
    {
        int sum = 0;
        bool isSecondDigit = false;
        
        number = number.Replace(" ", "");

        if (number.Length < 2)
        {
            return false;
        }
        
        for (int i = number.Length - 1; i >= 0; i--)
        {
            char c = number[i];
            if (!char.IsDigit(c))
                return false;
            
            int v = (int)c - '0';

            if (isSecondDigit)
            {
                v *= 2;
                if (v > 9)
                    v -= 9;
            }

            sum += v;
            isSecondDigit = !isSecondDigit;

        }
        
        return sum % 10 == 0;
    }
}