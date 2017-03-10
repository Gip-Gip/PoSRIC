#PoSRIC
The **Po**rtable **S**cripted **R**iPorFS **I**nterface in **C**89

##What is PoSRIC?

PoSRIC is a program that interfaces with RiPorFS using commands. It strives to
(one day) provide a portable and powerful interface to RiPorFS archives that
both beginners and DOS dwellers can use.

##What are the current features?

As of Version IV.IV.MMXVII Revision 0 there is

 * Basic stdio command interpretation
 * Basic scripting
 * Basic archive handling with directory support
 * BASH colors
 * Linux and Intel Mac Compatability
 * Depends on the Sweer library

##Where can I find more info?

README.PDF is the manual for PoSRIC where most of the documentation is written.
It needs vast improvements but currently it's all I'm willing to put out.

##How can I improve the source?

At the current moment PoSRIC is really unoptimized, and has a long way to go if
it ever wants to compete with TAR or ZIP. Currently I would like help with;

 * Adding/fixing comments
 * Improving documentation
 * Translating documentation
 * Improving the code
 * Add more code
 * Building for other platforms

Contributors will be placed in AUTHORS.TXT and listed in the authors splash of
PoSRIC

##Misc

 * The Versioning scheme is [Inf. Version].[Annual Version].[Year] in roman
   numerals
     * The Infinitive Version is incremented every large change, such as when
     PoSRIC became capable of IO with RiPorFS it was incremented from I to II
     * The Annual Version is incremented with the Infinitive Version and every
       large update which isn't drastic enough to increment the Infinitive
       Version. It is reset to one annually
 * PoSRIC has been tested on Debian and Mac OS 10.6.8
 * As of Version IV.IV.MMXVII Revision 0 the line count is 2520 (using
   sloccount)

