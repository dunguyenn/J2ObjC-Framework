//
//  Generated by the J2ObjC translator.  DO NOT EDIT!
//  source: /Users/tball/tmp/j2objc/junit/build_result/java/org/hamcrest/core/IsAnything.java
//

#ifndef _OrgHamcrestCoreIsAnything_H_
#define _OrgHamcrestCoreIsAnything_H_

#include <j2objc/J2ObjC_header.h>
#include <j2objc/org/hamcrest/BaseMatcher.h>

@protocol OrgHamcrestDescription;
@protocol OrgHamcrestMatcher;

@interface OrgHamcrestCoreIsAnything : OrgHamcrestBaseMatcher

#pragma mark Public

- (instancetype)init;

- (instancetype)initWithNSString:(NSString *)message;

+ (id<OrgHamcrestMatcher>)anything;

+ (id<OrgHamcrestMatcher>)anythingWithNSString:(NSString *)description_;

- (void)describeToWithOrgHamcrestDescription:(id<OrgHamcrestDescription>)description_;

- (jboolean)matchesWithId:(id)o;

@end

J2OBJC_EMPTY_STATIC_INIT(OrgHamcrestCoreIsAnything)

FOUNDATION_EXPORT void OrgHamcrestCoreIsAnything_init(OrgHamcrestCoreIsAnything *self);

FOUNDATION_EXPORT OrgHamcrestCoreIsAnything *new_OrgHamcrestCoreIsAnything_init() NS_RETURNS_RETAINED;

FOUNDATION_EXPORT void OrgHamcrestCoreIsAnything_initWithNSString_(OrgHamcrestCoreIsAnything *self, NSString *message);

FOUNDATION_EXPORT OrgHamcrestCoreIsAnything *new_OrgHamcrestCoreIsAnything_initWithNSString_(NSString *message) NS_RETURNS_RETAINED;

FOUNDATION_EXPORT id<OrgHamcrestMatcher> OrgHamcrestCoreIsAnything_anything();

FOUNDATION_EXPORT id<OrgHamcrestMatcher> OrgHamcrestCoreIsAnything_anythingWithNSString_(NSString *description_);

J2OBJC_TYPE_LITERAL_HEADER(OrgHamcrestCoreIsAnything)

#endif // _OrgHamcrestCoreIsAnything_H_