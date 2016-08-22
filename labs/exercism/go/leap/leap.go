package leap

const testVersion = 2

// Returns true if |x| can be divided by |y| without a rest.
func isDividedBy(x int, y int) bool {
	return x%y == 0
}

// Returns true if |year| is a leap year.
func IsLeapYear(year int) bool {
	return isDividedBy(year, 4) && (!isDividedBy(year, 100) || isDividedBy(year, 400))
}
