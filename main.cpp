#include <iostream>
#include <string>
using namespace std;

enum SyntaxKind
{
    NumberToken,
    WhitespaceToken,
    PlusToken,
    MinusToken,
    MultipleToken,
    DivisionToken,
    OpenedParenthesisToken,
    ClosedParenthesisToken,
    BadToken,
    EndOfFileToken,
};

class SyntaxToken
{
public:
    SyntaxKind _kind;
    int _position;
    string _text;

    SyntaxToken(SyntaxKind kind, int position, string text)
    {
        _kind = kind;
        _position = position;
        _text = text;
    }
    SyntaxKind getSyntaxKind()
    {
        return _kind;
    }
    int getPosition()
    {
        return _position;
    }
    string getText()
    {
        return _text;
    }
};

class Lexer
{
public:
    Lexer(string text)
    {
        _text = text;
    };

private:
    string _text;
    int _position = 0;

    char Current()
    {
        if (_position >= _text.length())
            return '\0';
        return _text[_position];
    };

    void Next()
    {
        _position++;
    }

public:
    SyntaxToken NextToken()
    {
        // numbers
        // + - * / , <white space> , ()

        if (_position >= _text.length())
        {
            return SyntaxToken(EndOfFileToken, _position, "\0");
        }

        if (isdigit(Current()))
        {
            int start = _position;

            while (isdigit(Current()))
                Next();

            int length = _position - start;
            string text = _text.substr(start, length);
            return SyntaxToken(NumberToken, start, text);
        }

        if (isspace(Current()))
        {
            int start = _position;

            while (isspace(Current()))
                Next();

            int length = _position - start;
            string text = _text.substr(start, length);
            return SyntaxToken(WhitespaceToken, start, text);
        }

        if ('+' == Current())
            return SyntaxToken(PlusToken, _position++, "+");
        else if ('-' == Current())
            return SyntaxToken(MinusToken, _position++, "-");
        else if ('*' == Current())
            return SyntaxToken(MultipleToken, _position++, "*");
        else if ('/' == Current())
            return SyntaxToken(DivisionToken, _position++, "/");
        else if ('(' == Current())
            return SyntaxToken(OpenedParenthesisToken, _position++, "(");
        else if (')' == Current())
            return SyntaxToken(ClosedParenthesisToken, _position++, ")");
        return SyntaxToken(BadToken, _position++, _text.substr(_position - 1, 1));
    }
};

int main()
{
    while (true)
    {
        string userInput;
        cout << "> ";
        getline(cin, userInput);
        if (userInput.empty())
        {
            return 0;
        }
        auto lexer = Lexer(userInput);
        while (true)
        {
            auto token = lexer.NextToken();
            if (token._kind == EndOfFileToken)
                break;
            cout << token.getSyntaxKind() << token.getText() << endl;
        }
    }

    return 0;
}
