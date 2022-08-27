#include <squirrel.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sqstdio.h>
#include <sqstdmath.h>
#include <sqstdstring.h>
#include <sqstdsystem.h>
#include <ctime>
#include <string>

void print_function(HSQUIRRELVM vm, const SQChar* message, ...)
{
    char buffer[1024];
    va_list marker;
    va_start(marker, message);
    scvsprintf(buffer, 1024, message, marker);
    va_end(marker);
    printf("%s\n", buffer);
}

void error_function(HSQUIRRELVM vm, const SQChar* message, ...)
{
    char buffer[1024];
    va_list marker;
    va_start(marker, message);
    scvsprintf(buffer, 1024, message, marker);
    va_end(marker);
    printf("<error> %s\n", buffer);
}

void compilier_error_function(HSQUIRRELVM vm, const SQChar *error_message, const SQChar *source, SQInteger line_number, SQInteger column_number)
{
    printf("<compilation_error> Error %s at %s line %lld column %lld\n", error_message, source, line_number, column_number);
}

SQInteger on_error_function(HSQUIRRELVM vm)
{
    if (sq_gettop(vm) >= 1)
    {
        const SQChar *error_message = 0;
        if (SQ_SUCCEEDED(sq_getstring(vm, 2, &error_message)))
        {
            printf("on_error: %s\n", error_message);
        }
    }
    return SQ_OK;
}

HSQUIRRELVM create_vm()
{
    // This is stack size 
    int stack_size = 100;

    // Here we are creating instance and storing it into vm variable
    HSQUIRRELVM vm = sq_open(stack_size);

    return vm;
}

void init_vm(HSQUIRRELVM vm)
{
    // Push root table
    sq_pushroottable(vm);

    // Setup callbacks
    sq_setprintfunc(vm, &print_function, &error_function);
    sq_setcompilererrorhandler(vm, &compilier_error_function);
    sq_newclosure(vm, &on_error_function, 0);
    sq_seterrorhandler(vm);

    // Pop root table
    sq_pop(vm, 1);
}

void init_vm_libraries(HSQUIRRELVM vm)
{
    // Register libraries
    sqstd_register_iolib(vm);
    sqstd_register_mathlib(vm);
    sqstd_register_stringlib(vm);
    sqstd_register_systemlib(vm);
}

void execute_script(HSQUIRRELVM vm, const char* source)
{
    // Save vm stack size
    int __top__ = sq_gettop(vm);

    // First let's compile source code
    if (SQ_SUCCEEDED(sq_compilebuffer(vm, source, strlen(source), "inline", SQTrue /* Raise compilation error if any*/)))
    {
        // Now on the top of stack we have squirrel closure
        // Extract compile closure
        HSQOBJECT compiled_clsoure;
        sq_getstackobj(vm, -1, &compiled_clsoure);
        sq_addref(vm, &compiled_clsoure);
        sq_pop(vm, -1);

        // Push root table
        sq_pushroottable(vm);

        // Call this closure just compiled without returning value into stack
        if (SQ_SUCCEEDED(sq_call(vm, 1, SQFalse /* Return value */, SQTrue /* Raise Error */)))
        {
        }
        else
        {
        }
        sq_release(vm, &compiled_clsoure);
    }
    else
    {
        printf("Unable to compile script: %s\n", source);
    }
    sq_settop(vm, __top__);
}

void format_date(const char* format, int msg_size, char* msg, int date)
{

    tm _time;
    _time.tm_year = (date / 10000) % 10000 - 1900;
    _time.tm_mon = (date / 100) % 100 - 1;
    _time.tm_mday = date % 100;

    // Do some formatting logic 
    strftime(msg, msg_size, format, &_time);
}

SQInteger vm_call_format_date(HSQUIRRELVM vm)
{
    // Get number of arguments. __top__ will be number of arguments + 1, since 
    // first element at the stack will be function object
    int __top__ = sq_gettop(vm);

    // Check that function got 2 elements on the stack
    if (__top__ == 3)
    {
        // If first argument int and second string
        if (sq_gettype(vm, 2) == OT_INTEGER && sq_gettype(vm, 3) == OT_STRING)
        {
            // Get first argument stored at index 2
            SQInteger date;
            sq_getinteger(vm, 2, &date);

            // Get second argument stored at index 3
            const SQChar* format;
            sq_getstring(vm, 3, &format);

            char msg[60];

            format_date(format, sizeof (msg), msg, date);

            // And result at msg buffer. -1 to force squirrel to get string length
            sq_pushstring(vm, msg, -1);

            // Should return 1, since we just pushed return value into stack
            return 1;
        }
    }
    // Should return 0, since we not return any values to stack
    return 0;
}

void init_function(HSQUIRRELVM vm)
{
    // Store stack size
    int __top__ = sq_gettop(vm);

    // Push root table
    sq_pushroottable(vm);

    // Function name
    sq_pushstring(vm, _SC("format_date"), -1);
    // Creating new closure in root table at stack => creating function
    sq_newclosure(vm, &vm_call_format_date, 0);
    // Disabling parameters checks, since will check in function 
    sq_setparamscheck(vm, 0, NULL);
    // Since it is native function, we should define it's name
    sq_setnativeclosurename(vm, -1, _SC("format_date"));
    // Here we are creating new slot in root table and this finally assigning name to function
    if (SQ_FAILED(sq_newslot(vm, -3, SQTrue)))
    {
        printf("Unable to register format_date\n");
    }
    // Restore stack size
    sq_settop(vm, __top__);
}

/**
 * Class that represents storage in YYYYMMDD andwhich makes from 20221001 
 * integer 1 November 2022
 */
class Date
{
public:
    /* Date storage integer */
    int date;

    Date() :
    date(0)
    {
    }

    Date(int date) :
    date(date)
    {
    }

    ~Date()
    {
    }

    int get_date()
    {
        return this->date;
    }

    void set_date(int date)
    {
        this->date = date;
    }

    std::string to_string()
    {
        // Here we are calling predefined function from previous section
        char msg[60];
        format_date("%Y/%m/%d", sizeof (msg), msg, this->date);
        return msg;
    }

    int get_year() const
    {
        return (this->date / 10000) % 10000;
    }

    int get_month() const
    {
        return (this->date / 100) % 100;
    }

    int get_day() const
    {
        return (this->date) % 100;
    }
};

SQInteger vm_destructor(SQUserPointer pointer, SQInteger size)
{
    Date* date = static_cast<Date*> (pointer);
    if (date) delete date;
    return SQ_OK;
}

SQInteger vm_constructor(HSQUIRRELVM vm)
{
    // Get number of arguments. __top__ will be number of arguments + 1, since 
    // first element at the stack will be function object
    int __top__ = sq_gettop(vm);

    // Default constructor
    if (__top__ == 1)
    {
        Date* date = new Date();
        if (SQ_FAILED(sq_setinstanceup(vm, 1, date)))
        {
            delete date;
            return sq_throwerror(vm, "Cannot create class instance 'date'");
        }

        // Add release hookthat this method will be called when by script vm
        // To destroy instance
        sq_setreleasehook(vm, 1, &vm_destructor);
    }
    else if (__top__ == 2)
    {
        // Constructor from int
        SQInteger date_int;
        sq_getinteger(vm, 2, &date_int);
        Date* date = new Date(date_int);
        if (SQ_FAILED(sq_setinstanceup(vm, 1, date)))
        {
            delete date;
            return sq_throwerror(vm, "Cannot create class instance 'date'");
        }

        // Add release hookthat this method will be called when by script vm
        // To destroy instance
        sq_setreleasehook(vm, 1, &vm_destructor);
    }

    return 0;
}

SQInteger vm_get_date(HSQUIRRELVM vm)
{   
    int __top__ = sq_gettop(vm);
    if (__top__ == 1)
    {
        SQUserPointer obj_ptr;
        if (SQ_FAILED(sq_getinstanceup(vm, 1, &obj_ptr, NULL))) 
        {
            return sq_throwerror(vm, "Unable to get instamce");
        }
        else
        {
            Date* obj = static_cast<Date*>(obj_ptr);
            int result = obj->get_date();
            sq_pushinteger(vm, result);
            return 1; // Return value
        }
    }
    return 0; // No return value
}

SQInteger vm_set_date(HSQUIRRELVM vm)
{   
    int __top__ = sq_gettop(vm);
    if (__top__ == 2)
    {
        SQUserPointer obj_ptr;
        if (SQ_FAILED(sq_getinstanceup(vm, 1, &obj_ptr, NULL))) 
        {
            return sq_throwerror(vm, "Unable to get instamce");
        }
        else
        {
            Date* obj = static_cast<Date*>(obj_ptr);
            
            SQInteger value;
            sq_getinteger(vm, 2, &value);
            
            obj->set_date(value);
            return 0; // No return value
        }
    }
    return 0; // No return value
}

SQInteger vm_get_year(HSQUIRRELVM vm)
{   
    int __top__ = sq_gettop(vm);
    if (__top__ == 1)
    {
        SQUserPointer obj_ptr;
        if (SQ_FAILED(sq_getinstanceup(vm, 1, &obj_ptr, NULL))) 
        {
            return sq_throwerror(vm, "Unable to get instamce");
        }
        else
        {
            Date* obj = static_cast<Date*>(obj_ptr);
            int result = obj->get_year();
            sq_pushinteger(vm, result);
            return 1; // Return value
        }
    }
    return 0; // No return value
}

SQInteger vm_get_month(HSQUIRRELVM vm)
{   
    int __top__ = sq_gettop(vm);
    if (__top__ == 1)
    {
        SQUserPointer obj_ptr;
        if (SQ_FAILED(sq_getinstanceup(vm, 1, &obj_ptr, NULL))) 
        {
            return sq_throwerror(vm, "Unable to get instamce");
        }
        else
        {
            Date* obj = static_cast<Date*>(obj_ptr);
            int result = obj->get_month();
            sq_pushinteger(vm, result);
            return 1; // Return value
        }
    }
    return 0; // No return value
}

SQInteger vm_get_day(HSQUIRRELVM vm)
{   
    int __top__ = sq_gettop(vm);
    if (__top__ == 1)
    {
        SQUserPointer obj_ptr;
        if (SQ_FAILED(sq_getinstanceup(vm, 1, &obj_ptr, NULL))) 
        {
            return sq_throwerror(vm, "Unable to get instamce");
        }
        else
        {
            Date* obj = static_cast<Date*>(obj_ptr);
            int result = obj->get_day();
            sq_pushinteger(vm, result);
            return 1; // Return value
        }
    }
    return 0; // No return value
}


SQInteger vm_to_string(HSQUIRRELVM vm)
{   
    int __top__ = sq_gettop(vm);
    if (__top__ == 1)
    {
        SQUserPointer obj_ptr;
        if (SQ_FAILED(sq_getinstanceup(vm, 1, &obj_ptr, NULL))) 
        {
            return sq_throwerror(vm, "Unable to get instamce");
        }
        else
        {
            Date* obj = static_cast<Date*>(obj_ptr);
            std::string result = obj->to_string();
            sq_pushstring(vm, result.c_str(), result.length());
            return 1; // Return value
        }
    }
    return 0; // No return value
}

void init_class(HSQUIRRELVM vm)
{
    // Store stack size
    int __top__ = sq_gettop(vm);

    // Push root table
    sq_pushroottable(vm);

    // Push class name
    sq_pushstring(vm, _SC("date"), -1);

    // Define class
    if (SQ_FAILED(sq_newclass(vm, SQFalse /* Has no base class*/)))
    {
        printf("Failed to create class: date\n");
        sq_settop(vm, __top__);
        return;
    }
    
    HSQOBJECT cls;
    sq_resetobject(&cls);
    sq_getstackobj(vm, -1, &cls);
    sq_addref(vm, &cls);
    
    // Constructor
    sq_pushstring(vm, _SC("constructor"), -1);
    sq_newclosure(vm, &vm_constructor, 0);
    sq_setparamscheck(vm, 0, NULL);
    sq_setnativeclosurename(vm, -1, _SC("constructor"));
    if (SQ_FAILED(sq_newslot(vm, -3, SQFalse)))
    {
        printf("Failed to create contructor for date\n");
        sq_settop(vm, __top__);
        return;
    }
    
    // get_date
    sq_pushstring(vm, _SC("get_date"), -1);
    sq_newclosure(vm, &vm_get_date, 0);
    sq_setparamscheck(vm, 0, NULL);
    sq_setnativeclosurename(vm, -1, _SC("get_date"));
    if (SQ_FAILED(sq_newslot(vm, -3, SQFalse)))
    {
        printf("Failed to create 'get_date' for date\n");
        sq_settop(vm, __top__);
        return;
    }
    
    // set_date
    sq_pushstring(vm, _SC("set_date"), -1);
    sq_newclosure(vm, &vm_get_date, 0);
    sq_setparamscheck(vm, 0, NULL);
    sq_setnativeclosurename(vm, -1, _SC("set_date"));
    if (SQ_FAILED(sq_newslot(vm, -3, SQFalse)))
    {
        printf("Failed to create 'set_date' for date\n");
        sq_settop(vm, __top__);
        return;
    }
    
    // get_year
    sq_pushstring(vm, _SC("get_year"), -1);
    sq_newclosure(vm, &vm_get_year, 0);
    sq_setparamscheck(vm, 0, NULL);
    sq_setnativeclosurename(vm, -1, _SC("get_year"));
    if (SQ_FAILED(sq_newslot(vm, -3, SQFalse)))
    {
        printf("Failed to create 'get_year' for date\n");
        sq_settop(vm, __top__);
        return;
    }
    
    // get_month
    sq_pushstring(vm, _SC("get_month"), -1);
    sq_newclosure(vm, &vm_get_month, 0);
    sq_setparamscheck(vm, 0, NULL);
    sq_setnativeclosurename(vm, -1, _SC("get_month"));
    if (SQ_FAILED(sq_newslot(vm, -3, SQFalse)))
    {
        printf("Failed to create 'get_month' for date\n");
        sq_settop(vm, __top__);
        return;
    }
    
    // get_day
    sq_pushstring(vm, _SC("get_day"), -1);
    sq_newclosure(vm, &vm_get_day, 0);
    sq_setparamscheck(vm, 0, NULL);
    sq_setnativeclosurename(vm, -1, _SC("get_day"));
    if (SQ_FAILED(sq_newslot(vm, -3, SQFalse)))
    {
        printf("Failed to create 'get_day' for date\n");
        sq_settop(vm, __top__);
        return;
    }
    
    // to_string
    sq_pushstring(vm, _SC("_tostring"), -1);
    sq_newclosure(vm, &vm_to_string, 0);
    sq_setparamscheck(vm, 0, NULL);
    sq_setnativeclosurename(vm, -1, _SC("_tostring"));
    if (SQ_FAILED(sq_newslot(vm, -3, SQFalse)))
    {
        printf("Failed to create '_str' for date\n");
        sq_settop(vm, __top__);
        return;
    }
    
    if (SQ_FAILED(sq_newslot(vm, -3, SQFalse)))
    {
        sq_settop(vm, __top__);
        return;
    }
    sq_settop(vm, __top__);
}

void execute_init(HSQUIRRELVM vm, const char* path) 
{
    int __top__ = sq_gettop(vm);
    
    // Push root table
    sq_pushroottable(vm);

    sq_pushstring(vm, _SC("init"), -1);
    if (SQ_FAILED(sq_get(vm, -2)))
    {
        printf("<error> Unable to find function init()\n");
        sq_settop(vm, __top__);
        return;
    }
    // Remove root table
    sq_remove(vm, -2);

    // Push root table
    sq_pushroottable(vm);

    // Push string argument
    sq_pushstring(vm, path, strlen(path));

    // Call method
    if (SQ_FAILED(sq_call(vm, 2, SQTrue /* Return value */  , SQTrue /* Enable error reporting */)))
    {
        printf("<error> Unable to call init()\n");
        return;
    }
    
    sq_settop(vm, __top__);
}

void create_unit_instance(HSQUIRRELVM vm, const char* class_name, const char* instance_name, const char* name, HSQOBJECT& result)
{
    // Reset result => make it null
    sq_resetobject(&result);
    
    int __top__ = sq_gettop(vm);
    
    sq_pushroottable(vm);
    sq_pushstring(vm, class_name, -1);
    
    // Get derived class 
    if (SQ_FAILED(sq_get(vm, -2)))
    {
        printf("<error> Unable to get class '%s'\n", class_name);
        sq_settop(vm, __top__);
        return;
    }
    
    sq_remove(vm, -2);      // Remove the root table
    sq_pushroottable(vm);   // Push root table on top
    
    
    // Push name to contructor
    sq_pushstring(vm, name, -1);
    
    // Create class instance
    if (SQ_FAILED(sq_call(vm, 2, SQTrue /* Constructor return value */ , SQTrue /* Enable error reporting */)))
    {
        printf("<error> Unable to call contructor '%s'\n", class_name);
        sq_settop(vm, __top__);
        return;
    }
    sq_remove(vm, -2);  //removes the class
    
    // Get resulting object from stack
    if (SQ_FAILED(sq_getstackobj(vm, -1, &result)))
    {
        printf("<error> Unable to get create instance of '%s'\n", class_name);
        sq_settop(vm, __top__);
        return;
    }
    
    // Save it into root table with name
    sq_pushroottable(vm);
    sq_pushstring(vm, instance_name, -1);
    sq_pushobject(vm, result);
    if (SQ_FAILED(sq_newslot(vm, -3, SQFalse)))
    {
        printf("<error> Unable to store into root table '%s'\n", class_name);
        sq_settop(vm, __top__);
        return;
    }

    sq_settop(vm, __top__);
}

void call_unit_run(HSQUIRRELVM vm, HSQOBJECT& object)
{
    int __top__ = sq_gettop(vm);
    
    sq_pushroottable(vm);
    sq_pushobject(vm, object);
    
    // Get method run
    sq_pushstring(vm, _SC("run"), -1);
    if (SQ_FAILED(sq_get(vm, -2)))
    {
        printf("<error> Unable to get method run\n");
        sq_settop(vm, __top__);
        return;
    }
    
    // Push object to call
    sq_pushobject(vm, object);
    
    // Call method
    if (SQ_FAILED(sq_call(vm, 1 /* Since don't have any parameters*/ , SQFalse /* No return value */  , SQTrue /* Enable error reporting */)))
    {
        printf("<error> Unable to get method run\n");
        sq_settop(vm, __top__);
        return;
    }
    
    sq_settop(vm, __top__);
}

int main()
{
    HSQUIRRELVM vm = create_vm();
    init_vm(vm);
    init_vm_libraries(vm);

    execute_script(vm, "print(\"Hello, World!\")");

    init_function(vm);

    execute_script(vm, "print(format_date(20220115,\"%m/%d/%Y\"))");
    
    init_class(vm);
    
    execute_script(vm, "d <- date(20220723)\n"
                       "print(d.get_year() + \"/\" + d.get_month() + \"/\" + d.get_day()  + \" str=\" + d.tostring())");

    execute_script(vm, "function init(path) { print(\"Loading from path: \" + path)}");
    
    execute_init(vm, "/my_test_path");
    
    execute_script(vm, "class Unit {\n"
        "    name = null\n"
        "    constructor(name) {\n"
        "       this.name = name\n"
        "    }\n"
        "    function attack() {\n"
        "       print(\"attack\")\n"
        "    }\n"
        "    function run() {\n"
        "       print(\"run\")\n"
        "    }\n"
        "}");
    
    execute_script(vm, "class UnitA extends Unit{\n"
        "    constructor(name) {\n"
        "       base.constructor(name)\n"
        "    }\n"
        "    function attack() {\n"
        "       print(\"UnitA: \" + name + \" attack\")\n"
        "    }\n"
        "    function run() {\n"
        "       print(\"UnitA: \" + name + \" run\")\n"
        "    }\n"
        "}");
    
    HSQOBJECT super_soldier;
    create_unit_instance(vm, "UnitA", "soldier", "super soldier", super_soldier);
    call_unit_run(vm, super_soldier);
    
    return 0;
}
