package hello

const testVersion = 2

func HelloWorld(name string) string {
	if len(name) == 0 {
		return "Hello, World!"
	} else {
		return "Hello, " + name + "!"
	}
}
