package swp4.test;

import swp4.test.annotation.TestClass;
import swp4.test.annotation.TestMethod;
import swp4.test.exception.TestRunnerException;
import swp4.util.ConsoleColors;

import java.lang.reflect.Method;
import java.util.Arrays;
import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.Stream;

public class TestRunner {
    private List<Class<?>> testClasses;
    private AtomicInteger count = new AtomicInteger(0);
    private AtomicInteger passed = new AtomicInteger(0);
    private AtomicInteger failed = new AtomicInteger(0);
    private AtomicInteger ignored = new AtomicInteger(0);

    public static void run(Class<?> ... testCLasses) throws TestRunnerException {
        new TestRunner(testCLasses).execute();
    }

    protected TestRunner(Class<?> ... testClasses) {
        this.testClasses = Arrays.asList(testClasses);
    }

    private void execute() throws TestRunnerException {
        if(this.testClasses == null || this.testClasses.isEmpty()) {
            throw new TestRunnerException("No test classes provided, test execution aborted.");
        }

        for(Class<?> testClass : testClasses) {
            if(testClass.isAnnotationPresent(TestClass.class)) {
                TestClass testClassAnnotation = testClass.getAnnotation(TestClass.class);
                System.out.println("Running test class: "+ ConsoleColors.BLUE + testClass.getName() + ConsoleColors.RESET);
                System.out.println("Test class created by: "+testClassAnnotation.createdBy());
                System.out.println("Test class description: "+testClassAnnotation.description());

                processAndExecuteTestMethods(testClass);

            } else {
                System.err.println("Class "+ testClass.getName() + " does not provide a @TestClass annotation, so skipping!");
            }
        }
    }

    private void processAndExecuteTestMethods(Class<?> testClass) {
        Method[] methods = testClass.getDeclaredMethods();
        if(methods == null || methods.length == 0) {
            System.err.println("No methods found for class "+testClass.getName());
        } else {
            Stream<Method> methodStream = Arrays.stream(methods);
            // verify if method has @TestMethod annotation - if present, execute method
            methodStream.filter(m -> m.isAnnotationPresent(TestMethod.class))
                    .parallel() // EASY PEASY THREADING
                    .forEach(method -> {
                        TestMethod testMethodAnnotation = method.getAnnotation(TestMethod.class);
                        if(testMethodAnnotation.enabled()) {
                            try {
                                method.invoke(testClass.getDeclaredConstructor(new Class[]{}).newInstance());
                                System.out.printf(ConsoleColors.GREEN+"%s - Test - '%s' - passed%n"+ConsoleColors.RESET, count.getAndIncrement(), method.getName());
                                passed.incrementAndGet();
                            } catch (Throwable ex) {
                                System.out.printf(ConsoleColors.RED+"%s - Test - '%s' - failed: %s%n"+ConsoleColors.RESET, count.getAndIncrement(), method.getName(), ex.getCause());
                                failed.incrementAndGet();
                            }
                        } else {
                            System.out.printf(ConsoleColors.YELLOW+"%s - Test '%s' - ignored%n"+ConsoleColors.RESET,count.getAndIncrement(), method.getName());
                            ignored.incrementAndGet();
                        }
                    });
            System.out.println("\nResult \n------------------------------------");
            System.out.printf("Total: %d, Passed: %d, Failed: %d, Ignored: %d%n", count.get(), passed.get(), failed.get(), ignored.get());
        }
    }
}
