# Progamming manifesto

Rules which should qualify to each language, so, my lang should use them whenever
it is possible, if there is exception it should be mentioned with the rationale.
At this point the order of rules is random.

## Syntax

### Formatting the code

#### Rule 1

Even if you can write many expression in one line with semilocon, just don't do  
that. Split expressions by lines whenever they're doing other things, and in
most cases they do.


Rationale: [Linux kernel coding style](https://www.kernel.org/doc/html/v4.10/process/coding-style.html#placing-braces-and-spaces)


(C lang example)  
OK:  
```c
if (c == 0) {
    a = b;
    c = 1;
}
```
OK:  
```c
if (boolean == 0)
    a = b;
```  
BAD:  
```c
if (c == 0) { a = b; c = 1; }
```
BAD:  
```c
if (boolean == 0) a = b;
```

---

#### Rule 2

The length of line should be shorter than 80 characters. If there is REALLY good
reason for longer line, 100 characters should be hard cap.

---

#### Rule 3

Whenever you have to break function, list, tuple or other type of long code add
just one tab more than the previous line.  
(Banana flavored example)  
OK:
```
    a := b.do(
        something,
        with,
        some,
        variables
    );
```
BAD:
```
    a := b.do(  something,
                with,
                some,
                variables);
```
Rationale:  
This way, code is way more readable. Look how books, papers and good websites
are formatted, it unusual for our eyes to have simply empty space during the
reading. Also look at harder examples, where variable names are way longer and
there is also more brackets.

< tutaj przyklad jesli kiedys znajde >

---

#### Rule 4

The length of each file should be around 100 SLOC. Files should go to this size,
and having a lot of small files is also bad idea.

Rationale: Uncle Bob, personal experience. Over 100 lines of code is way less
readable. More than this is bloat, hard to read code. Ofc, that is not hard cap,
just split the code responsibly.

## Classes

### Variables

#### Rule 1

If you see over 5-6 variables in the class, probably they are not needed.
take a better look and move the variables into the methods. The point of this
rule is more about finding potential bug and code smells, rather than solid,
hardcapped axiom.

Rationale: my observations.

---

#### Rule 2

Getters and setters are not always needed. Sometimes they're great and useful
but in many scenarios leaving the variable as a public is good enough.

Rationale: Doing getter and setter for every single small variable, also often
being simple type like integer or string, is not needed, java degenerates often
shows that as great thing, I see it as a boilerplate. Use setters, where
variable validation is needed, and getter in cases where reading the state can
change it, that's rule of thumb.

## Logic

### Planing and the mental part

#### Rule 1

Write logic first, then start to remove repetition.

Rationale: Great talk,
[*The mental game of Python*](https://youtu.be/Uwuv05aZ6ug?si=kYUAK-o0vuv21JER)

## Intefraces

### Where they are needed

#### Rule 1

Don't spam with intefraces, whenever you see that maybe it will be needed.
As in rule 1 in **logic->Planing and the mental part**

Rationale:
Interfaces (in class manner) written only for futher development right now are
literraly bloat, you don't need them.

## Curing Java's degerenacy

### Rationale of the whole segment

Java and java people tends to favor (sometimes even pressure at work or uni)
quite specific rules, which don't make sense until you're building some sort of
big ENTERPRISE project. My suggestion is just to avoid situation where you need
big ENTERPRISE project at the first place - things at that size become really
hard to properly manage, and what is even more important - they're bloated af.
Whenever you look into large enterprise project you will see deprecated
functions, not used anymore interfaces, and other evidence of situations like
"oh, I don't use it but also I cannot remove that cause project is not working
at all without it". This naturally evolves over time to such absurds like famous
[coconut image](https://www.thegamer.com/this-coconut-jpg-in-team-fortress-2s-game-files-if-deleted-breaks-the-game-and-no-one-knows-why/)
from Team Fortress 2. My strong opinion is that every code is bad code, so the
less code you write the better for you and your system's stability.


Many of myths and degenerateous java propraganada are still to this day set as a
standard in computer science. Many of them also get their own rules (e.g. 
**Classes->Variables->Rule 1**), but some of them are so oddly specific that 
I written this chapter only for them.

### Java degeneracy top practices

#### Rule 1

Don't add javadoc/doxygen/sphinx or any other kind of documentation for each
method/class in existence. Document only the big ones, who cannot be explained
by sole reading the code, and public interfaces, used by programmers or users.

Rationale: Whenever you have to document everything you will automaticly tend to
document really precise small function, and do overall documentation of big ones.
That is in our nature - people don't like to work, especially if it's something
obligatory, we are lazy creatures. Document things which you (or user) really
need to understand deeply, leaving the focus to do that only in real need.