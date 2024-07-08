using System;

public static class SimpleCalculator
{
    public static string Calculate(int operand1, int operand2, string operation)
    {
        int result = 0;
        switch (operation)
        {
            case null:
                throw new ArgumentNullException();
            
            case "":
                throw new ArgumentException();
            
            case "+":
                result = operand1 + operand2;
                break;
            
            case "*":
                result = operand1 * operand2;
                break;

            case "/":
                try
                {
                    result = operand1 / operand2;
                }
                catch (DivideByZeroException)
                {
                    return "Division by zero is not allowed.";
                }
                
                break;
            
            default:
                throw new ArgumentOutOfRangeException();
        }

        return $"{operand1} {operation} {operand2} = {result}";
    }
}
