using System.Diagnostics;

/*const string data = """
                    3   4
                    4   3
                    2   5
                    1   3
                    3   9
                    3   3
                    """;

string[] lines = data.Split("\r\n");*/

List<int> a = [];
List<int> b = [];
int distance = 0;
int similarity = 0;

string[] lines = File.ReadAllLines("../../../data/day1.txt");

foreach (string line in lines)
{
    string[] v = line.Split("   ");
    a.Add(int.Parse(v[0]));
    b.Add(int.Parse(v[1]));
}

a.Sort();
b.Sort();

Debug.WriteLine("a = " + string.Join(", ", a));
Debug.WriteLine("b = " + string.Join(", ", b));

// Part 1

for (int i = 0; i < a.Count; i++)
{
    distance += int.Abs(a[i] - b[i]);
}

Console.WriteLine("distance = " + distance);

// Part 2

foreach (int v in a)
{
    int count = b.Where(x => x.Equals(v))
        .Select(x => x)
        .Count();
    similarity += v * count;
}

Console.WriteLine("similarity = " + similarity);