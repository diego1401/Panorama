// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

namespace Imagine {
    /// \addtogroup Common
    /// @{

    /// version of libraries.
    /// String contining version of Imagine++ libraries
    ///
    /// \dontinclude Common/test/test.cpp \skip base()
    /// \skipline version number
    const std::string VERSION="4.3.2";

    /// \def srcPath(s)
    /// Transform relative file path to absolute path.
    /// This macro prepends its argument with the absolute path of the folder
    /// containing the source file. The argument (a file name relative path)
    /// must be a C constant string, like "data.txt". This does not work with a
    /// variable, see stringSrcPath for that.
    /// \param s File name as a C constant string 
    /// \return Absolute path (a C constant string)
    /// \sa stringSrcPath
    ///
    /// \dontinclude Common/test/test.cpp \skip base()
    /// \skipline C source path
    ///
    /// \def stringSrcPath
    /// Transform relative file path to absolute path.
    /// This macro prepends its argument with the absolute path of the folder
    /// containing the source file. The argument (a file name relative path)
    /// is a C++ string variable.
    /// \param s File name as a C++ string
    /// \return Absolute path as a C++ string
    /// \sa srcPath
    ///
    /// \dontinclude Common/test/test.cpp \skip base()
    /// \skipline String source path
    /// \skipline ...
#ifdef SRCDIR
    // Using CMake.
#define SP_STRINGIFY(s)  #s
#define SP_EVAL(s) SP_STRINGIFY(s)
#define srcPath(s) (SP_EVAL(SRCDIR)"/" s)
#define stringSrcPath(s) (SP_EVAL(SRCDIR)"/"+std::string(s))
#else
    // Not using CMake. Created by Windows wizard...
#define srcPath(s) (s)
#define stringSrcPath(s) (s)
#endif

    ///@}
}
