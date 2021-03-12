package swp4.basics.greeter;

public class Greeter {
    public static void main(String[] args)
    {
        if(args.length > 0)
            System.out.println("Hello " + args[0] + "!");
        else
            System.out.println("Please provide a parameter, who you want to greet!");
    }
}
