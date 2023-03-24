public class StringLiteralExample {
    public static void main(String args[]) {
        // Single-line comment
        System.out.println("Hello, world!"); // Single-line comment at end of line

        /* Multi-line comment
           that spans
           multiple lines */
        System.out.println("This is a multi-line\nstring literal."); // String literal with newline escape sequence

        // Escape sequences in string literals
        System.out.println("This is a double quote (\") and this is a backslash (\\).");
        System.out.println("This is a tab character (\t) and this is a carriage return (\r).");
        
        // Text block with leading/trailing whitespaces
        String textBlock1 = """
                             This is a text block
                             that contains leading and trailing
                             whitespaces.
                            """;
        System.out.println(textBlock1);

        // Text block without leading/trailing whitespaces
        String textBlock2 = """
                            This is a text block
                            that does not contain leading and trailing
                            whitespaces."""; // Trailing backslash escape sequence to continue on next line
        System.out.println(textBlock2);

        // Escaped text block with no leading/trailing whitespaces
        String textBlock3 = """
                            This is a text block with a backslash (\\)
                            at the end of the first line \\
                            and on the second line.""";
        System.out.println(textBlock3);
    }
}
