//
//  Generated by the J2ObjC translator.  DO NOT EDIT!
//  source: android/libcore/luni/src/main/java/java/util/concurrent/CyclicBarrier.java
//

#ifndef _JavaUtilConcurrentCyclicBarrier_H_
#define _JavaUtilConcurrentCyclicBarrier_H_

#include <j2objc/J2ObjC_header.h>

@class JavaUtilConcurrentTimeUnitEnum;
@protocol JavaLangRunnable;

/*!
 @brief A synchronization aid that allows a set of threads to all wait for
 each other to reach a common barrier point.
 CyclicBarriers are
 useful in programs involving a fixed sized party of threads that
 must occasionally wait for each other. The barrier is called
 <em>cyclic</em> because it can be re-used after the waiting threads
 are released.
 <p>A <code>CyclicBarrier</code> supports an optional <code>Runnable</code> command
 that is run once per barrier point, after the last thread in the party
 arrives, but before any threads are released.
 This <em>barrier action</em> is useful
 for updating shared-state before any of the parties continue.
 <p><b>Sample usage:</b> Here is an example of
 using a barrier in a parallel decomposition design:
 @code
 
  class Solver 
   final int N;
   final float[][] data;
   final CyclicBarrier barrier;
   class Worker implements Runnable {
     int myRow;
     Worker(int row) { myRow = row; }
     public void run() {
       while (!done()) {
         processRow(myRow);
         try {
           barrier.await();
         } catch (InterruptedException ex) {
           return;
         } catch (BrokenBarrierException ex) {
           return;
         }
       }
     }
   }
   public Solver(float[][] matrix) {
     data = matrix;
     N = matrix.length;
     barrier = new CyclicBarrier(N,
                                 new Runnable() {
                                   public void run() {
                                     mergeRows(...);
                                   }
                                 });
     for (int i = 0; i < N; ++i)
       new Thread(new Worker(i)).start();
     waitUntilDone();
   }
  
@endcode
 Here, each worker thread processes a row of the matrix then waits at the
 barrier until all rows have been processed. When all rows are processed
 the supplied <code>Runnable</code> barrier action is executed and merges the
 rows. If the merger
 determines that a solution has been found then <code>done()</code> will return
 <code>true</code> and each worker will terminate.
 <p>If the barrier action does not rely on the parties being suspended when
 it is executed, then any of the threads in the party could execute that
 action when it is released. To facilitate this, each invocation of
 <code>await</code> returns the arrival index of that thread at the barrier.
 You can then choose which thread should execute the barrier action, for
 example:
 @code
 
  if (barrier.await() == 0) 
   // log the completion of this iteration
  
@endcode
 <p>The <code>CyclicBarrier</code> uses an all-or-none breakage model
 for failed synchronization attempts: If a thread leaves a barrier
 point prematurely because of interruption, failure, or timeout, all
 other threads waiting at that barrier point will also leave
 abnormally via <code>BrokenBarrierException</code> (or
 <code>InterruptedException</code> if they too were interrupted at about
 the same time).
 <p>Memory consistency effects: Actions in a thread prior to calling
 <code>await()</code>
 <a href="package-summary.html#MemoryVisibility"><i>happen-before</i></a>
 actions that are part of the barrier action, which in turn
 <i>happen-before</i> actions following a successful return from the
 corresponding <code>await()</code> in other threads.
 @since 1.5
 @author Doug Lea
 */
@interface JavaUtilConcurrentCyclicBarrier : NSObject

#pragma mark Public

/*!
 @brief Creates a new <code>CyclicBarrier</code> that will trip when the
 given number of parties (threads) are waiting upon it, and
 does not perform a predefined action when the barrier is tripped.
 @param parties the number of threads that must invoke <code>await</code>
 before the barrier is tripped
 @throws IllegalArgumentException if <code>parties</code> is less than 1
 */
- (instancetype)initWithInt:(jint)parties;

/*!
 @brief Creates a new <code>CyclicBarrier</code> that will trip when the
 given number of parties (threads) are waiting upon it, and which
 will execute the given barrier action when the barrier is tripped,
 performed by the last thread entering the barrier.
 @param parties the number of threads that must invoke <code>await</code>
 before the barrier is tripped
 @param barrierAction the command to execute when the barrier is
 tripped, or <code>null</code> if there is no action
 @throws IllegalArgumentException if <code>parties</code> is less than 1
 */
- (instancetype)initWithInt:(jint)parties
       withJavaLangRunnable:(id<JavaLangRunnable>)barrierAction;

/*!
 @brief Waits until all parties have invoked
 <code>await</code> on this barrier.
 <p>If the current thread is not the last to arrive then it is
 disabled for thread scheduling purposes and lies dormant until
 one of the following things happens:
 <ul>
 <li>The last thread arrives; or
 <li>Some other thread interrupts
 the current thread; or
 <li>Some other thread interrupts
 one of the other waiting threads; or
 <li>Some other thread times out while waiting for barrier; or
 <li>Some other thread invokes <code>reset</code> on this barrier.
 </ul>
 <p>If the current thread:
 <ul>
 <li>has its interrupted status set on entry to this method; or
 <li>is interrupted while waiting
 </ul>
 then <code>InterruptedException</code> is thrown and the current thread's
 interrupted status is cleared.
 <p>If the barrier is <code>reset</code> while any thread is waiting,
 or if the barrier is broken when
 <code>await</code> is invoked, or while any thread is waiting, then
 <code>BrokenBarrierException</code> is thrown.
 <p>If any thread is interrupted while waiting,
 then all other waiting threads will throw
 <code>BrokenBarrierException</code> and the barrier is placed in the broken
 state.
 <p>If the current thread is the last thread to arrive, and a
 non-null barrier action was supplied in the constructor, then the
 current thread runs the action before allowing the other threads to
 continue.
 If an exception occurs during the barrier action then that exception
 will be propagated in the current thread and the barrier is placed in
 the broken state.
 @return the arrival index of the current thread, where index
 <code>getParties() - 1</code> indicates the first
 to arrive and zero indicates the last to arrive
 @throws InterruptedException if the current thread was interrupted
 while waiting
 @throws BrokenBarrierException if <em>another</em> thread was
 interrupted or timed out while the current thread was
 waiting, or the barrier was reset, or the barrier was
 broken when <code>await</code> was called, or the barrier
 action (if present) failed due to an exception
 */
- (jint)await;

/*!
 @brief Waits until all parties have invoked
 <code>await</code> on this barrier, or the specified waiting time elapses.
 <p>If the current thread is not the last to arrive then it is
 disabled for thread scheduling purposes and lies dormant until
 one of the following things happens:
 <ul>
 <li>The last thread arrives; or
 <li>The specified timeout elapses; or
 <li>Some other thread interrupts
 the current thread; or
 <li>Some other thread interrupts
 one of the other waiting threads; or
 <li>Some other thread times out while waiting for barrier; or
 <li>Some other thread invokes <code>reset</code> on this barrier.
 </ul>
 <p>If the current thread:
 <ul>
 <li>has its interrupted status set on entry to this method; or
 <li>is interrupted while waiting
 </ul>
 then <code>InterruptedException</code> is thrown and the current thread's
 interrupted status is cleared.
 <p>If the specified waiting time elapses then <code>TimeoutException</code>
 is thrown. If the time is less than or equal to zero, the
 method will not wait at all.
 <p>If the barrier is <code>reset</code> while any thread is waiting,
 or if the barrier is broken when
 <code>await</code> is invoked, or while any thread is waiting, then
 <code>BrokenBarrierException</code> is thrown.
 <p>If any thread is interrupted while
 waiting, then all other waiting threads will throw <code>BrokenBarrierException</code>
  and the barrier is placed in the broken
 state.
 <p>If the current thread is the last thread to arrive, and a
 non-null barrier action was supplied in the constructor, then the
 current thread runs the action before allowing the other threads to
 continue.
 If an exception occurs during the barrier action then that exception
 will be propagated in the current thread and the barrier is placed in
 the broken state.
 @param timeout the time to wait for the barrier
 @param unit the time unit of the timeout parameter
 @return the arrival index of the current thread, where index
 <code>getParties() - 1</code> indicates the first
 to arrive and zero indicates the last to arrive
 @throws InterruptedException if the current thread was interrupted
 while waiting
 @throws TimeoutException if the specified timeout elapses
 @throws BrokenBarrierException if <em>another</em> thread was
 interrupted or timed out while the current thread was
 waiting, or the barrier was reset, or the barrier was broken
 when <code>await</code> was called, or the barrier action (if
 present) failed due to an exception
 */
- (jint)awaitWithLong:(jlong)timeout
withJavaUtilConcurrentTimeUnitEnum:(JavaUtilConcurrentTimeUnitEnum *)unit;

/*!
 @brief Returns the number of parties currently waiting at the barrier.
 This method is primarily useful for debugging and assertions.
 @return the number of parties currently blocked in <code>await</code>
 */
- (jint)getNumberWaiting;

/*!
 @brief Returns the number of parties required to trip this barrier.
 @return the number of parties required to trip this barrier
 */
- (jint)getParties;

/*!
 @brief Queries if this barrier is in a broken state.
 @return <code>true</code> if one or more parties broke out of this
 barrier due to interruption or timeout since
 construction or the last reset, or a barrier action
 failed due to an exception; <code>false</code> otherwise.
 */
- (jboolean)isBroken;

/*!
 @brief Resets the barrier to its initial state.
 If any parties are
 currently waiting at the barrier, they will return with a
 <code>BrokenBarrierException</code>. Note that resets <em>after</em>
 a breakage has occurred for other reasons can be complicated to
 carry out; threads need to re-synchronize in some other way,
 and choose one to perform the reset.  It may be preferable to
 instead create a new barrier for subsequent use.
 */
- (void)reset;

@end

J2OBJC_EMPTY_STATIC_INIT(JavaUtilConcurrentCyclicBarrier)

FOUNDATION_EXPORT void JavaUtilConcurrentCyclicBarrier_initWithInt_withJavaLangRunnable_(JavaUtilConcurrentCyclicBarrier *self, jint parties, id<JavaLangRunnable> barrierAction);

FOUNDATION_EXPORT JavaUtilConcurrentCyclicBarrier *new_JavaUtilConcurrentCyclicBarrier_initWithInt_withJavaLangRunnable_(jint parties, id<JavaLangRunnable> barrierAction) NS_RETURNS_RETAINED;

FOUNDATION_EXPORT void JavaUtilConcurrentCyclicBarrier_initWithInt_(JavaUtilConcurrentCyclicBarrier *self, jint parties);

FOUNDATION_EXPORT JavaUtilConcurrentCyclicBarrier *new_JavaUtilConcurrentCyclicBarrier_initWithInt_(jint parties) NS_RETURNS_RETAINED;

J2OBJC_TYPE_LITERAL_HEADER(JavaUtilConcurrentCyclicBarrier)

#endif // _JavaUtilConcurrentCyclicBarrier_H_