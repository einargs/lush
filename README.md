# Lush
Lush is a functional, compiled language written in the vein of Haskell. It is
designed to be whitespace insensitive while still avoiding the need to use
curly-braces or keywords to begin and end scopes. Further, Lush is designed to
be highly extensible, with features built in from the start that allow for the
creation of powerful DSLs, macros, and the ability to easily adjust compiler
behavior.

# Why Lush?
Lush is not truly written to fulfill any great need; rather, it is written as a
way to learn more about how compilers, parsers, lexers, language theory, and
languages as a whole operate.

In other words, Lush is objectively unlikely to succeed as a project.

With that said, there is an overall vision for Lush's future. The end goal of
this project is to have an extensible, powerful language with strong typing in
the vein of Haskell that allows for the easy creation of DSLs and other
languages.

# Where is Lush right now?
Lush is still in the very, very early stages of development. The current plan is
to write an initial compiler in C++ using LLVM. Once that is working at least
somewhat well, the project can begin to work on implementing more of the
compiler in lush, with the eventual goal being complete self-hosting, with the
likely exception of callouts to specialized C and C++ wrapper code around the
LLVM API in order to generate the LLVM IR.

## Why self-hosted?
There are two main reasons to have the vast majority of the Lush compiler
written in Lush itself. The first is due to a practice called "Dogfooding",
which refers to the idea of eating your own dogfood: it is a lot easier to find
bugs and areas where new features are needed when you use on a daily basis the
tool that you are developing. By using Lush to write Lush's own compiler,
it will be possible to quickly identify areas of improvement both in syntax
and in performance.

The second reason is that some of Lush's features that involve modification of
the compiler's behavior will be easier to write when both the compiler-side
and the program-side of the process are in the same language.

## What does "modify the compiler's behavior" mean?
Before beginning, it is important to note that the behavior described below
is far from implementation. These are pie-in-the-sky hopes for what Lush may
one day be capable of, and not something that is anywhere near implementation.

One of the language constructs in Lush is the annotation, which consists of
the `@` symbol followed by an expression. Annotations basically pass the
compiler a "message" consisting of the value of the expression following it.
The compiler can then handle this message as it sees fit.

An example message would be the import system in Lush, which uses annotations
to tell the compiler that it needs to load another file.

```
@import #[greet] from: "./greeter"
```

The import function takes the arguments that you can see there and returns
a data structure that represents the message telling the compiler that it needs
to load the `greet` variable from the `./greeter.lush` file into the current
file's context.

Another example works like this:

```
@import #[pugLang] from: "@pug"
@import #[template `as` mainPageTemplate]
        from: "./view/main-page.pug"
        using: pugLang
```

Here we get to see one of the really cool parts of Lush in action. First we
import the variable `pugLang` from `@pug`. The first thing that sticks out
is most likely the `@` in front of the `pug` in `@pug`; this character indicates
that `pug` is a library that should be loaded differently from a normal file.

Next, we see the ``@import #[template `as` mainPageTemplate]`` line, which is
just saying that the template variable should be imported under a new name.

However, what we're really interested in is the `using: pugLang`. This piece of
code is telling `@import` to tell the compiler that it should basically stick
`@pugLang` at the top of whatever file it loads--in other words, the `using`
option means that the compiler is passed the `pugLang` message before it even
reads the first character of the `./view/main-page.pug` file.

This is extremely useful because `pug` here is a HTML template library, and
the message `pugLang` contains tells the compiler how to parse a `.pug` file
into a fast Lush function that accepts a few environmental variables and uses
them to create a string of HTML that can then be served to the visitor of a
website or some such.

(The name `pug` was chosen as a homage to the NodeJS HTML template library of
the same name.)

It's even possible to simplify the template import:

```
@import #[pugImport] from: "@pug"
@pugImport #mainPageTemplate from: "./view/main-page"
```

By defining a helper function `pugImport`:

```
@import #[Quote.VarRef] from: "@std/quote"
@import #[Import.Msg] from: "@std/loader"
@import #[pugLang] from "@pug"

Quote.VarRef -> from: Str -> Import.Msg
pugImport {:var_ref varName} from: path =
  Str fullPath = path ++ ".pug"
  import #[&varName] from: fullPath using: pugLang

(export #[pugImport])
```

The takeaway from all of this is that Lush is intended to offer first-class
support to domain-specific languages like template languages as well as other
full-blown programming languages (through the Foreign Function Interface)
through a powerful ability to alter the compiler's behavior by passing
messages to it.

Of course, none of this is anywhere even close to being implemented. Even a
generous estimate suggests that two-to-four years of work will be necessary
before the above examples are actually practical.
