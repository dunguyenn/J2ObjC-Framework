//
//  Generated by the J2ObjC translator.  DO NOT EDIT!
//  source: android/libcore/luni/src/main/java/java/io/FilterReader.java
//

#include "../../J2ObjC_header.h"

#pragma push_macro("INCLUDE_ALL_JavaIoFilterReader")
#ifdef RESTRICT_JavaIoFilterReader
#define INCLUDE_ALL_JavaIoFilterReader 0
#else
#define INCLUDE_ALL_JavaIoFilterReader 1
#endif
#undef RESTRICT_JavaIoFilterReader

#pragma clang diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#if !defined (JavaIoFilterReader_) && (INCLUDE_ALL_JavaIoFilterReader || defined(INCLUDE_JavaIoFilterReader))
#define JavaIoFilterReader_

#define RESTRICT_JavaIoReader 1
#define INCLUDE_JavaIoReader 1
#include "../../java/io/Reader.h"

@class IOSCharArray;

/*!
 @brief Wraps an existing <code>Reader</code> and performs some transformation on the
 input data while it is being read.
 Transformations can be anything from a
 simple byte-wise filtering input data to an on-the-fly compression or
 decompression of the underlying reader. Readers that wrap another reader and
 provide some additional functionality on top of it usually inherit from this
 class.
 - seealso: FilterWriter
 */
@interface JavaIoFilterReader : JavaIoReader {
 @public
  /*!
   @brief The target Reader which is being filtered.
   */
  JavaIoReader *in_;
}

#pragma mark Public

/*!
 @brief Closes this reader.
 This implementation closes the filtered reader.
 @throws IOException
 if an error occurs while closing this reader.
 */
- (void)close;

/*!
 @brief Sets a mark position in this reader.
 The parameter <code>readlimit</code>
 indicates how many bytes can be read before the mark is invalidated.
 Sending <code>reset()</code> will reposition this reader back to the marked
 position, provided that <code>readlimit</code> has not been surpassed.
 <p>
 This implementation sets a mark in the filtered reader.
 @param readlimit
 the number of bytes that can be read from this reader before
 the mark is invalidated.
 @throws IOException
 if an error occurs while marking this reader.
 - seealso: #markSupported()
 - seealso: #reset()
 */
- (void)markWithInt:(jint)readlimit;

/*!
 @brief Indicates whether this reader supports <code>mark()</code> and <code>reset()</code>.
 This implementation returns whether the filtered reader supports marking.
 @return <code>true</code> if <code>mark()</code> and <code>reset()</code> are supported
 by the filtered reader, <code>false</code> otherwise.
 - seealso: #mark(int)
 - seealso: #reset()
 - seealso: #skip(long)
 */
- (jboolean)markSupported;

/*!
 @brief Reads a single character from the filtered reader and returns it as an
 integer with the two higher-order bytes set to 0.
 Returns -1 if the end
 of the filtered reader has been reached.
 @return The character read or -1 if the end of the filtered reader has
 been reached.
 @throws IOException
 if an error occurs while reading from this reader.
 */
- (jint)read;

/*!
 @brief Reads up to <code>count</code> characters from the filtered reader and stores them
 in the byte array <code>buffer</code> starting at <code>offset</code>.
 Returns the
 number of characters actually read or -1 if no characters were read and
 the end of the filtered reader was encountered.
 @throws IOException
 if an error occurs while reading from this reader.
 */
- (jint)readWithCharArray:(IOSCharArray *)buffer
                  withInt:(jint)offset
                  withInt:(jint)count;

/*!
 @brief Indicates whether this reader is ready to be read without blocking.
 If
 the result is <code>true</code>, the next <code>read()</code> will not block. If
 the result is <code>false</code>, this reader may or may not block when
 <code>read()</code> is sent.
 @return <code>true</code> if this reader will not block when <code>read()</code>
 is called, <code>false</code> if unknown or blocking will occur.
 @throws IOException
 if the reader is closed or some other I/O error occurs.
 */
- (jboolean)ready;

/*!
 @brief Resets this reader's position to the last marked location.
 Invocations of
 <code>read()</code> and <code>skip()</code> will occur from this new location. If
 this reader was not marked, the behavior depends on the implementation of
 <code>reset()</code> in the Reader subclass that is filtered by this reader.
 The default behavior for Reader is to throw an <code>IOException</code>.
 @throws IOException
 if a problem occurred or the filtered reader does not support
 <code>mark()</code> and <code>reset()</code>.
 - seealso: #mark(int)
 - seealso: #markSupported()
 */
- (void)reset;

/*!
 @brief Skips <code>charCount</code> characters in this reader.
 Subsequent calls to <code>read</code>
 will not return these characters unless <code>reset</code> is used. The
 default implementation is to skip characters in the filtered reader.
 @return the number of characters actually skipped.
 @throws IOException
 if the filtered reader is closed or some other I/O error
 occurs.
 - seealso: #mark(int)
 - seealso: #markSupported()
 - seealso: #reset()
 */
- (jlong)skipWithLong:(jlong)charCount;

#pragma mark Protected

/*!
 @brief Constructs a new FilterReader on the Reader <code>in</code>.
 @param inArg
 The non-null Reader to filter reads on.
 */
- (instancetype)initWithJavaIoReader:(JavaIoReader *)inArg;

@end

J2OBJC_EMPTY_STATIC_INIT(JavaIoFilterReader)

J2OBJC_FIELD_SETTER(JavaIoFilterReader, in_, JavaIoReader *)

FOUNDATION_EXPORT void JavaIoFilterReader_initWithJavaIoReader_(JavaIoFilterReader *self, JavaIoReader *inArg);

J2OBJC_TYPE_LITERAL_HEADER(JavaIoFilterReader)

#endif


#pragma clang diagnostic pop
#pragma pop_macro("INCLUDE_ALL_JavaIoFilterReader")
