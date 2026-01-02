#include <iostream>

using namespace std;

/*
    attributes - contains elements of a given structure (list / queue / stack);

    symbol - in this program stores the symbol assigned to each operation:
    [ MIN : 'I', MAX : 'A', IF : 'F', N : 'N',
      + : '+', - : '-', * : '*', / : '/', ( : '(', ) : ')' ]
    AND if the element of a given structure stores a number (number != NULL),
    then symbol stores: 'L';

    number - stores some number, otherwise = NULL;

    next - pointer to the next element of the structure;

    prev - pointer to the previous element of the structure.
*/
struct Attributes {
    char symbol;
    int number;
    Attributes* next;
    Attributes* prev;
};

class List
{
public:
    List()
    {
        this->first = nullptr;
        this->last = nullptr;
    }

    void add_to_end_symbol(const char symbol)
    {
        /*
            create a new node and set its base values;
            since this is a symbol, set "number" to NULL
        */
        Attributes* new_node = new Attributes;
        new_node->symbol = symbol;
        new_node->number = NULL;
        new_node->next = nullptr;
        new_node->prev = nullptr;

        create_new_element_on_top(new_node);
    }

    void add_to_end_number(const int number)
    {
        /*
            create a new node and set its base values;
            since this is a number, set "symbol" to 'L'
            (we mark this element so we know to take values
            from the "number" field, not "symbol")
        */
        Attributes* new_node = new Attributes;
        new_node->symbol = 'L';
        new_node->number = number;
        new_node->next = nullptr;
        new_node->prev = nullptr;

        create_new_element_on_top(new_node);
    }

    /*
        method printing all elements of the structure from the back
        without removing any element
    */
    const void print_contents_from_back()
    {
        Attributes* tmp_list = this->last;

        while (tmp_list != nullptr)
        {
            print_attribute_value(tmp_list);
            tmp_list = tmp_list->prev;
        }
    }

    /*
        method printing all elements of the structure from the front
        without removing any element
    */
    const void print_contents_from_front()
    {
        Attributes* tmp_list = this->first;

        while (tmp_list != nullptr)
        {
            print_attribute_value(tmp_list);
            tmp_list = tmp_list->next;
        }
    }

    /*
        returns true if the structure has no elements
    */
    const bool is_empty() const
    {
        if (this->first != nullptr) return false;
        return true;
    }

    /*
        returns true if the first element stores a symbol
    */
    const bool is_first_value_a_symbol() const
    {
        if (this->first->symbol == 'L') return false;
        return true;
    }

    ~List()
    {
        while (this->first != nullptr)
        {
            /*
                if checks whether the structure still contains any element
                other than the first element
            */
            if (this->first->next == nullptr)
            {
                delete this->first;
                this->first = nullptr;
                this->last = nullptr;
            }
            else
            {
                this->last = this->last->prev;
                delete this->last->next;
                this->last->next = nullptr;
            }
        }
    }

protected:

    /*
        prints the element appropriately.
        MAX and MIN do not print a space, because after them comes
        a number telling how many elements they consider.
    */
    const void print_attribute_value(Attributes* tmp_list) const
    {
        switch (tmp_list->symbol)
        {
        case 'L':
            cout << tmp_list->number << " ";
            break;
        case 'A':
            cout << "MAX";
            break;
        case 'I':
            cout << "MIN";
            break;
        case 'F':
            cout << "IF" << " ";
            break;
        default:
            cout << tmp_list->symbol << " ";
        }
    }

    const void create_new_element_on_top(Attributes* new_node)
    {
        /*
            check if the structure has at least one element;
            if not, initialize it
        */
        if (this->last == nullptr) {
            this->first = new_node;
            this->last = new_node;
            return;
        }

        new_node->prev = this->last;
        this->last = new_node;

        /*
            set the next pointer of the previous element
            to point to the newly created element (new_node)
        */
        this->last->prev->next = new_node;
    }

    /*
        first - pointer to the first element of the structure;
        last  - pointer to the last element of the structure.
    */
    Attributes* first;
    Attributes* last;
};

class Stack : public virtual List
{
public:
    const void remove_from_end()
    {
        /*
            check if the structure has at least one element
        */
        if (this->first == nullptr) return;

        /*
            handle a structure containing only one element
        */
        if (this->first->next == nullptr)
        {
            delete this->first;
            this->first = nullptr;
            this->last = nullptr;
            return;
        }

        /*
            set the second-to-last element as the last
            and delete the previous last one
        */
        this->last = this->last->prev;
        delete this->last->next;
        this->last->next = nullptr;
    }

    int get_end_number() const
    {
        return this->last->number;
    }

    char get_end_symbol() const
    {
        return this->last->symbol;
    }
};

class Queue : public virtual List
{
public:
    const void remove_from_front()
    {
        /*
            check if the structure has at least one element
        */
        if (this->first == nullptr) return;

        /*
            handle a structure containing only one element
        */
        if (this->first->next == nullptr)
        {
            delete this->first;
            this->first = nullptr;
            this->last = nullptr;
            return;
        }

        /*
            set the second element as the first
            and delete the previous first one
        */
        this->first = this->first->next;
        delete this->first->prev;
        this->first->prev = nullptr;
    }

    const int get_front_number() const
    {
        return this->first->number;
    }

    const char get_front_symbol() const
    {
        return this->first->symbol;
    }
};

bool is_char_a_digit(char symbol)
{
    if (symbol >= '0' && symbol <= '9') return true;
    return false;
}

int char_to_int(char symbol)
{
    return int(symbol) - int('0');
}

/*
    I called all operations that extend the basic calculator
    "special operations" (MIN, MAX, N, IF)
*/
bool is_special_operation(char symbol)
{
    switch (symbol)
    {
    case 'N':
        return true;
    case 'I':
        return true;
    case 'A':
        return true;
    case 'F':
        return true;
    default:
        return false;
    }
}

/*
    returns the priority of each operator symbol
    all symbols have priority as suggested in the task,
    I only extended priority for ',' by giving it -1
*/
int get_priority(char symbol)
{
    if (symbol == '+' || symbol == '-') return 0;
    if (symbol == '*' || symbol == '/') return 1;
    if (symbol == 'N' || symbol == 'I' || symbol == 'A' || symbol == 'F') return 2;
    if (symbol == '(' || symbol == ')') return 3;
    return -1;
}

/*
    addition operation: takes two consecutive elements from the stack
    and removes them, then returns their sum
*/
int add_operation(Stack& stack)
{
    int op2, op1;
    op2 = stack.get_end_number();
    stack.remove_from_end();
    op1 = stack.get_end_number();
    stack.remove_from_end();

    return op1 + op2;
}

/*
    subtraction operation: takes two consecutive elements from the stack
    and removes them, then returns their difference
*/
int subtract_operation(Stack& stack)
{
    int op2, op1;

    op2 = stack.get_end_number();
    stack.remove_from_end();
    op1 = stack.get_end_number();
    stack.remove_from_end();

    return op1 - op2;
}

/*
    multiplication operation: takes two consecutive elements from the stack
    and removes them, then returns their product
*/
int multiply_operation(Stack& stack)
{
    int op2, op1;

    op2 = stack.get_end_number();
    stack.remove_from_end();
    op1 = stack.get_end_number();
    stack.remove_from_end();

    return op1 * op2;
}

/*
    division operation: takes two consecutive elements from the stack
    and removes them, then returns their quotient
*/
int divide_operation(Stack& stack)
{
    int op2, op1;

    op2 = stack.get_end_number();
    stack.remove_from_end();
    op1 = stack.get_end_number();
    stack.remove_from_end();

    return op1 / op2;
}

/*
    min operation: takes consecutive elements from the stack
    removes them, and finds the minimum
*/
int min_operation(Stack& stack, int n)
{
    int helper, minimum;

    minimum = stack.get_end_number();
    stack.remove_from_end();

    // start from i = 1 because we already removed one element from the stack
    for (int i = 1; i < n; i++)
    {
        helper = stack.get_end_number();
        stack.remove_from_end();
        if (helper < minimum) minimum = helper;
    }
    return minimum;
}

/*
    max operation: takes consecutive elements from the stack
    removes them, and finds the maximum
*/
int max_operation(Stack& stack, int n)
{
    int helper, maximum;
    maximum = stack.get_end_number();
    stack.remove_from_end();

    // start from i = 1 because we already removed one element from the stack
    for (int i = 1; i < n; i++)
    {
        helper = stack.get_end_number();
        stack.remove_from_end();
        if (helper > maximum) maximum = helper;
    }
    return maximum;
}

/*
    IF operation: takes three consecutive elements from the stack
    removes them.
    if condition > 0 return greater_than_zero, otherwise return less_than_zero
*/
int if_operation(Stack& stack)
{
    int less_than_zero, greater_than_zero, condition;
    less_than_zero = stack.get_end_number();
    stack.remove_from_end();
    greater_than_zero = stack.get_end_number();
    stack.remove_from_end();
    condition = stack.get_end_number();
    stack.remove_from_end();

    if (condition > 0) return greater_than_zero;
    return less_than_zero;
}

/*
    negation: takes one element from the stack, removes it,
    returns its negated value
*/
int negation_operation(Stack& stack)
{
    int op1;
    op1 = stack.get_end_number();
    stack.remove_from_end();

    return -1 * op1;
}

/*
    updates commas counting:
    - for MAX/MIN: push the number of arguments (commas_count + 1) into ONP queue
    - for IF: remove two unnecessary counted commas (meaning 3 numbers)
*/
void update_commas(Queue& onp, Stack& count_commas, char& symbol)
{
    if (symbol == 'A' || symbol == 'I')
    {
        onp.add_to_end_number(count_commas.get_end_number());
        count_commas.remove_from_end();
    }
    else if (symbol == 'F')
    {
        count_commas.remove_from_end();
    }
}

/*
    calculates the result.

    passed in: queue with computed RPN (ONP),
    an empty stack (reused),
    and char symbol (reused)
*/
void CalcRPN(Queue& onp, Stack& stack, char& symbol)
{
    while (!onp.is_empty())
    {
        /*
            if the first queue element is a number, push it onto the stack
            and update queue
        */
        if (!onp.is_first_value_a_symbol())
        {
            stack.add_to_end_number(onp.get_front_number());
            onp.remove_from_front();
        }
        else
        {
            symbol = onp.get_front_symbol();
            onp.remove_from_front();

            /*
                print operator symbol, similarly to method around line 145
            */
            if (symbol == 'A')
                cout << "MAX" << onp.get_front_number() << " ";
            else if (symbol == 'I')
                cout << "MIN" << onp.get_front_number() << " ";
            else if (symbol == 'F') cout << "IF" << " ";
            else cout << symbol << " ";

            /*
                print all numbers currently stored on the stack (from the back)
            */
            stack.print_contents_from_back();
            cout << '\n';

            /*
                handle each operation,
                and if division by zero occurs print "ERROR" and stop immediately
            */
            switch (symbol)
            {
            case '+':
                stack.add_to_end_number(add_operation(stack));
                break;
            case '-':
                stack.add_to_end_number(subtract_operation(stack));
                break;
            case '/':
                if (stack.get_end_number() != 0)
                    stack.add_to_end_number(divide_operation(stack));
                else
                {
                    cout << "ERROR" << '\n';
                    return;
                }
                break;
            case '*':
                stack.add_to_end_number(multiply_operation(stack));
                break;
            case 'N':
                stack.add_to_end_number(negation_operation(stack));
                break;
            case 'F': // IF
                stack.add_to_end_number(if_operation(stack));
                break;
            case 'A': // MAX
                // onp.get_front_number() = how many numbers this operation uses
                stack.add_to_end_number(max_operation(stack, onp.get_front_number()));
                onp.remove_from_front();
                break;
            case 'I': // MIN
                // onp.get_front_number() = how many numbers this operation uses
                stack.add_to_end_number(min_operation(stack, onp.get_front_number()));
                onp.remove_from_front();
            }
        }
    }
    // final result
    cout << stack.get_end_number() << '\n';
}

void RPN()
{
    /*
        count_commas - stack used to count how many arguments MIN/MAX/IF have;

        stack - operator stack (stores symbols like '+', 'N', ...);

        onp - queue where we store the conversion result (to RPN)
    */
    Stack count_commas;
    Stack stack;
    Queue onp;

    /*
        was_last_char_a_number - used to detect if in the current loop iteration
        we were reading a number

        symbol and top - store read characters (top is a helper)

        priority and number - helper variables
    */
    bool was_last_char_a_number = false;
    char symbol, top;
    int priority, number = 0;

    cin >> symbol;

    while (symbol != '.')
    {
        /*
            handles reading M - MIN/MAX or I - IF.
            necessary because these operations consist of 2-3 letters,
            and we read input character-by-character.
        */
        if (symbol == 'M' || symbol == 'I')
        {
            // map to [ MAX : 'A', MIN : 'I', IF : 'F' ]
            cin >> symbol;
            count_commas.add_to_end_number(1);

            /*
                if reading MAX or MIN, we still need to read the 3rd char (X or N),
                but it won't be used later
            */
            if (symbol != 'F')
            {
                cin >> top;
            }
        }

        if (is_char_a_digit(symbol))
        {
            /*
                if the read character was a digit, keep reading digits
                and build the full integer
            */
            do
            {
                number = number * 10 + char_to_int(symbol);
                cin >> symbol;
            } while (is_char_a_digit(symbol));

            // store the built number in the queue
            onp.add_to_end_number(number);

            // handle cases like: [ N N N 10 ]
            if (!stack.is_empty())
            {
                top = stack.get_end_symbol();

                while (top == 'N')
                {
                    onp.add_to_end_symbol(top);
                    stack.remove_from_end();
                    if (!stack.is_empty()) top = stack.get_end_symbol();
                    else break;
                }
            }

            number = 0;
            was_last_char_a_number = true;
        }
        else if (symbol == '(')
        {
            // if symbol is '(', push it onto the operator stack
            stack.add_to_end_symbol(symbol);
        }
        else if (symbol == ')')
        {
            /*
                loop until stack is empty or until '(' is found
            */
            while (!stack.is_empty())
            {
                symbol = stack.get_end_symbol();
                stack.remove_from_end();
                if (symbol == '(') break;
                else onp.add_to_end_symbol(symbol);
            }

            // handle cases like: [ N MIN ( 1 ) ]
            if (!stack.is_empty())
            {
                top = stack.get_end_symbol();

                while (is_special_operation(top))
                {
                    symbol = stack.get_end_symbol();
                    stack.remove_from_end();
                    onp.add_to_end_symbol(symbol);

                    update_commas(onp, count_commas, symbol);

                    if (!stack.is_empty()) top = stack.get_end_symbol();
                    else break;
                }
            }
        }
        else
        {
            /*
                handle remaining symbols according to infix->RPN conversion rules
            */
            priority = get_priority(symbol);
            while (!stack.is_empty())
            {
                top = stack.get_end_symbol();
                stack.remove_from_end();
                if (is_special_operation(top)
                    || top == '(' || get_priority(top) < priority)
                {
                    stack.add_to_end_symbol(top);

                    update_commas(onp, count_commas, top);
                    break;
                }
                onp.add_to_end_symbol(top);
            }

            /*
                if symbol == ',' then we do not push it to the stack
                and we increment the top value of count_commas by 1
            */
            if (symbol != ',') stack.add_to_end_symbol(symbol);
            else
            {
                number = count_commas.get_end_number() + 1;
                count_commas.remove_from_end();
                count_commas.add_to_end_number(number);
                number = 0;
            }
        }

        /*
            if we read a full number in this loop, we do NOT read another symbol here,
            because we already read one beyond the digits in the number-building loop.
        */
        if (!was_last_char_a_number) cin >> symbol;
        was_last_char_a_number = false;
    }

    /*
        move remaining operators from the stack to the queue,
        and clean the stack
    */
    while (!stack.is_empty())
    {
        symbol = stack.get_end_symbol();
        stack.remove_from_end();
        onp.add_to_end_symbol(symbol);

        update_commas(onp, count_commas, symbol);
    }

    // print final RPN conversion
    onp.print_contents_from_front();
    cout << '\n';

    CalcRPN(onp, stack, symbol);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int operations_count;
    cin >> operations_count;

    for (int i = 0; i < operations_count; i++) RPN();

    return 0;
}
