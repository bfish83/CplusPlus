#ifndef STRING215_H_INCLUDED
#define STRING215_H_INCLUDED

int test_string215();
void pause_215(bool have_newline);
int stringLength(const char *input);
char *copy_string(const char *input);
bool equal_string(const char *first, const char *second);

class string215
{
public:
	// Create a string215 of length zero (null terminator only).
	string215();
	// Create a string215 that is a (deep) copy of another.
	string215(const string215 &other);
	// Destroy a string215 and de-allocate its memory.
	~string215();

	// Return the length of a string215, not counting the null terminator.
	int length() const;
	// Return the character at a given index.  Returns '\0' if the
	// index is out of bounds.
	char getchar(int index) const;
	// Set the character at a given index and return false.
	bool setchar(int index, char newchar);
	// Check whether two strings contain the same characters.
	bool equals(const string215 &other) const;
	// Add a suffix to the end of this string.  Allocates and frees memory.
	void append(const string215 &suffix);
	// Return a pointer to the raw character data (not a copy).
	const char *c_str() const;
	// Replace the contents of this string215 with a copy of a C string.  Allocates and frees memory.
	void replace(const char *in_str);
	// Create a string215 that is a (deep) copy of a C string.
	string215(const char *in_str);

private:
	// Pointer to a null-terminated character array storing this object's content.
	char *data;
};

#endif