using System;

public static class PlayAnalyzer
{
    public static string AnalyzeOnField(int shirtNum)
    {
        switch (shirtNum)
        {
            case 1:
                return "goalie";
            case 2:
                return "left back";
            case 3:
            case 4:
                return "center back";
            case 5:
                return "right back";
            case 6:
            case 7:
            case 8:
                return "midfielder";
            case 9:
                return "left wing";
            case 10:
                return "striker";
            case 11:
                return "right wing";
            default:
                throw new ArgumentOutOfRangeException();
        }
    }

    public static string AnalyzeOffField(object report)
    {
        return report switch
        {
            int supportersInStadium => $"There are {supportersInStadium} supporters at the match.",
            
            string announcerMessage => announcerMessage,

            Injury injury => $"Oh no! {injury.GetDescription()} Medics are on the field.",

            Foul foul => foul.GetDescription(),
            
            Incident incident => incident.GetDescription(),
            
            Manager { Club: not null } manager => $"{manager.Name} ({manager.Club})",
            
            Manager manager => $"{manager.Name}",
            
            _ => throw new ArgumentException(),
        };
    }
}
