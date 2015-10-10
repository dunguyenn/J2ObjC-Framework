//
//  Generated by the J2ObjC translator.  DO NOT EDIT!
//  source: android/frameworks/base/core/java/android/os/AsyncTask.java
//

#ifndef _AndroidOsAsyncTask_H_
#define _AndroidOsAsyncTask_H_

#include <j2objc/J2ObjC_header.h>
#include <j2objc/java/lang/Enum.h>

@class AndroidOsAsyncTask_StatusEnum;
@class IOSObjectArray;
@class JavaUtilConcurrentTimeUnitEnum;
@protocol JavaLangRunnable;
@protocol JavaUtilConcurrentExecutor;

/*!
 @brief <p>AsyncTask enables proper and easy use of the UI thread.
 This class allows to
 perform background operations and publish results on the UI thread without
 having to manipulate threads and/or handlers.</p>
 <p>AsyncTask is designed to be a helper class around <code>Thread</code>
 and does not constitute a generic threading framework. AsyncTasks should ideally be
 used for short operations (a few seconds at the most.) If you need to keep threads
 running for long periods of time, it is highly recommended you use the various APIs
 provided by the <code>java.util.concurrent</code> package such as <code>Executor</code>,
 <code>ThreadPoolExecutor</code> and <code>FutureTask</code>.</p>
 <p>An asynchronous task is defined by a computation that runs on a background thread and
 whose result is published on the UI thread. An asynchronous task is defined by 3 generic
 types, called <code>Params</code>, <code>Progress</code> and <code>Result</code>,
 and 4 steps, called <code>onPreExecute</code>, <code>doInBackground</code>,
 <code>onProgressUpdate</code> and <code>onPostExecute</code>.</p>
 <h2>Usage</h2>
 <p>AsyncTask must be subclassed to be used. The subclass will override at least
 one method (<code>doInBackground</code>), and most often will override a
 second one (<code>onPostExecute</code>.)</p>
 <p>Here is an example of subclassing:</p>
 <pre class="prettyprint">
 private class DownloadFilesTask extends AsyncTask&lt;URL, Integer, Long&gt; {
 protected Long doInBackground(URL... urls) {
 int count = urls.length;
 long totalSize = 0;
 for (int i = 0; i < count; i++) {
 totalSize += Downloader.downloadFile(urls[i]);
 publishProgress((int) ((i / (float) count) * 100));
 // Escape early if cancel() is called
 if (isCancelled()) break;
 }
 return totalSize;
 }
 protected void onProgressUpdate(Integer... progress) {
 setProgressPercent(progress[0]);
 }
 protected void onPostExecute(Long result) {
 showDialog("Downloaded " + result + " bytes");
 }
 }
 
@endcode
 <p>Once created, a task is executed very simply:</p>
 <pre class="prettyprint">
 new DownloadFilesTask().execute(url1, url2, url3);
 
@endcode
 <h2>AsyncTask's generic types</h2>
 <p>The three types used by an asynchronous task are the following:</p>
 <ol>
 <li><code>Params</code>, the type of the parameters sent to the task upon
 execution.</li>
 <li><code>Progress</code>, the type of the progress units published during
 the background computation.</li>
 <li><code>Result</code>, the type of the result of the background
 computation.</li>
 </ol>
 <p>Not all types are always used by an asynchronous task. To mark a type as unused,
 simply use the type <code>Void</code>:</p>
 @code

  private class MyTask extends AsyncTask&lt;Void, Void, Void&gt; { ... }
  
@endcode
 <h2>The 4 steps</h2>
 <p>When an asynchronous task is executed, the task goes through 4 steps:</p>
 <ol>
 <li><code>onPreExecute()</code>, invoked on the UI thread before the task
 is executed. This step is normally used to setup the task, for instance by
 showing a progress bar in the user interface.</li>
 <li><code>doInBackground</code>, invoked on the background thread
 immediately after <code>onPreExecute()</code> finishes executing. This step is used
 to perform background computation that can take a long time. The parameters
 of the asynchronous task are passed to this step. The result of the computation must
 be returned by this step and will be passed back to the last step. This step
 can also use <code>publishProgress</code> to publish one or more units
 of progress. These values are published on the UI thread, in the
 <code>onProgressUpdate</code> step.</li>
 <li><code>onProgressUpdate</code>, invoked on the UI thread after a
 call to <code>publishProgress</code>. The timing of the execution is
 undefined. This method is used to display any form of progress in the user
 interface while the background computation is still executing. For instance,
 it can be used to animate a progress bar or show logs in a text field.</li>
 <li><code>onPostExecute</code>, invoked on the UI thread after the background
 computation finishes. The result of the background computation is passed to
 this step as a parameter.</li>
 </ol>
 <h2>Cancelling a task</h2>
 <p>A task can be cancelled at any time by invoking <code>cancel(boolean)</code>. Invoking
 this method will cause subsequent calls to <code>isCancelled()</code> to return true.
 After invoking this method, <code>onCancelled(Object)</code>, instead of
 <code>onPostExecute(Object)</code> will be invoked after <code>doInBackground(Object[])</code>
 returns. To ensure that a task is cancelled as quickly as possible, you should always
 check the return value of <code>isCancelled()</code> periodically from
 <code>doInBackground(Object[])</code>, if possible (inside a loop for instance.)</p>
 <h2>Threading rules</h2>
 <p>There are a few threading rules that must be followed for this class to
 work properly:</p>
 <ul>
 <li>The AsyncTask class must be loaded on the UI thread. This is done
 automatically as of JELLY_BEAN.</li>
 <li>The task instance must be created on the UI thread.</li>
 <li><code>execute</code> must be invoked on the UI thread.</li>
 <li>Do not call <code>onPreExecute()</code>, <code>onPostExecute</code>,
 <code>doInBackground</code>, <code>onProgressUpdate</code> manually.</li>
 <li>The task can be executed only once (an exception will be thrown if
 a second execution is attempted.)</li>
 </ul>
 <h2>Memory observability</h2>
 <p>AsyncTask guarantees that all callback calls are synchronized in such a way that the following
 operations are safe without explicit synchronizations.</p>
 <ul>
 <li>Set member fields in the constructor or <code>onPreExecute</code>, and refer to them
 in <code>doInBackground</code>.
 <li>Set member fields in <code>doInBackground</code>, and refer to them in
 <code>onProgressUpdate</code> and <code>onPostExecute</code>.
 </ul>
 <h2>Order of execution</h2>
 <p>When first introduced, AsyncTasks were executed serially on a single background
 thread. Starting with DONUT, this was changed
 to a pool of threads allowing multiple tasks to operate in parallel. Starting with
 HONEYCOMB, tasks are executed on a single
 thread to avoid common application errors caused by parallel execution.</p>
 <p>If you truly want parallel execution, you can invoke
 <code>executeOnExecutor(java.util.concurrent.Executor,Object[])</code> with
 <code>THREAD_POOL_EXECUTOR</code>.</p>
 */
@interface AndroidOsAsyncTask : NSObject

#pragma mark Public

/*!
 @brief Creates a new asynchronous task.
 This constructor must be invoked on the UI thread.
 */
- (instancetype)init;

/*!
 @brief <p>Attempts to cancel execution of this task.
 This attempt will
 fail if the task has already completed, already been cancelled,
 or could not be cancelled for some other reason. If successful,
 and this task has not started when <tt>cancel</tt> is called,
 this task should never run. If the task has already started,
 then the <tt>mayInterruptIfRunning</tt> parameter determines
 whether the thread executing this task should be interrupted in
 an attempt to stop the task.</p>
 <p>Calling this method will result in <code>onCancelled(Object)</code> being
 invoked on the UI thread after <code>doInBackground(Object[])</code>
 returns. Calling this method guarantees that <code>onPostExecute(Object)</code>
 is never invoked. After invoking this method, you should check the
 value returned by <code>isCancelled()</code> periodically from
 <code>doInBackground(Object[])</code> to finish the task as early as
 possible.</p>
 @param mayInterruptIfRunning <tt>true</tt> if the thread executing this
 task should be interrupted; otherwise, in-progress tasks are allowed
 to complete.
 @return <tt>false</tt> if the task could not be cancelled,
 typically because it has already completed normally;
 <tt>true</tt> otherwise
 */
- (jboolean)cancelWithBoolean:(jboolean)mayInterruptIfRunning;

/*!
 @brief Executes the task with the specified parameters.
 The task returns
 itself (this) so that the caller can keep a reference to it.
 <p>Note: this function schedules the task on a queue for a single background
 thread or pool of threads depending on the platform version.  When first
 introduced, AsyncTasks were executed serially on a single background thread.
 Starting with DONUT, this was changed
 to a pool of threads allowing multiple tasks to operate in parallel. Starting
 HONEYCOMB, tasks are back to being
 executed on a single thread to avoid common application errors caused
 by parallel execution.  If you truly want parallel execution, you can use
 the <code>executeOnExecutor</code> version of this method
 with <code>THREAD_POOL_EXECUTOR</code>; however, see commentary there for warnings
 on its use.
 <p>This method must be invoked on the UI thread.
 @param params The parameters of the task.
 @return This instance of AsyncTask.
 @throws IllegalStateException If <code>getStatus()</code> returns either
 <code>AsyncTask.Status.RUNNING</code> or <code>AsyncTask.Status.FINISHED</code>.
 */
- (AndroidOsAsyncTask *)executeWithNSObjectArray:(IOSObjectArray *)params;

/*!
 @brief Convenience version of <code>execute(Object...)
 </code> for use with
 a simple Runnable object. See <code>execute(Object[])</code> for more
 information on the order of execution.
 */
+ (void)executeWithJavaLangRunnable:(id<JavaLangRunnable>)runnable;

/*!
 @brief Executes the task with the specified parameters.
 The task returns
 itself (this) so that the caller can keep a reference to it.
 <p>This method is typically used with <code>THREAD_POOL_EXECUTOR</code> to
 allow multiple tasks to run in parallel on a pool of threads managed by
 AsyncTask, however you can also use your own <code>Executor</code> for custom
 behavior.
 <p><em>Warning:</em> Allowing multiple tasks to run in parallel from
 a thread pool is generally <em>not</em> what one wants, because the order
 of their operation is not defined.  For example, if these tasks are used
 to modify any state in common (such as writing a file due to a button click),
 there are no guarantees on the order of the modifications.
 Without careful work it is possible in rare cases for the newer version
 of the data to be over-written by an older one, leading to obscure data
 loss and stability issues.  Such changes are best
 executed in serial; to guarantee such work is serialized regardless of
 platform version you can use this function with <code>SERIAL_EXECUTOR</code>.
 <p>This method must be invoked on the UI thread.
 @param exec The executor to use.  <code>THREAD_POOL_EXECUTOR</code> is available as a
 convenient process-wide thread pool for tasks that are loosely coupled.
 @param params The parameters of the task.
 @return This instance of AsyncTask.
 @throws IllegalStateException If <code>getStatus()</code> returns either
 <code>AsyncTask.Status.RUNNING</code> or <code>AsyncTask.Status.FINISHED</code>.
 */
- (AndroidOsAsyncTask *)executeOnExecutorWithJavaUtilConcurrentExecutor:(id<JavaUtilConcurrentExecutor>)exec
                                                      withNSObjectArray:(IOSObjectArray *)params;

/*!
 @brief Waits if necessary for the computation to complete, and then
 retrieves its result.
 @return The computed result.
 @throws CancellationException If the computation was cancelled.
 @throws ExecutionException If the computation threw an exception.
 @throws InterruptedException If the current thread was interrupted
 while waiting.
 */
- (id)get;

/*!
 @brief Waits if necessary for at most the given time for the computation
 to complete, and then retrieves its result.
 @param timeout Time to wait before cancelling the operation.
 @param unit The time unit for the timeout.
 @return The computed result.
 @throws CancellationException If the computation was cancelled.
 @throws ExecutionException If the computation threw an exception.
 @throws InterruptedException If the current thread was interrupted
 while waiting.
 @throws TimeoutException If the wait timed out.
 */
- (id)getWithLong:(jlong)timeout
withJavaUtilConcurrentTimeUnitEnum:(JavaUtilConcurrentTimeUnitEnum *)unit;

/*!
 @brief Returns the current status of this task.
 @return The current status.
 */
- (AndroidOsAsyncTask_StatusEnum *)getStatus;

/*!
 @brief Returns <tt>true</tt> if this task was cancelled before it completed
 normally.
 If you are calling <code>cancel(boolean)</code> on the task,
 the value returned by this method should be checked periodically from
 <code>doInBackground(Object[])</code> to end the task as soon as possible.
 @return <tt>true</tt> if task was cancelled before it completed
 */
- (jboolean)isCancelled;

/*!
  
 */
+ (void)setDefaultExecutorWithJavaUtilConcurrentExecutor:(id<JavaUtilConcurrentExecutor>)exec;

#pragma mark Protected

/*!
 @brief Override this method to perform a computation on a background thread.
 The
 specified parameters are the parameters passed to <code>execute</code>
 by the caller of this task.
 This method can call <code>publishProgress</code> to publish updates
 on the UI thread.
 @param params The parameters of the task.
 @return A result, defined by the subclass of this task.
 */
- (id)doInBackgroundWithNSObjectArray:(IOSObjectArray *)params;

/*!
 @brief <p>Applications should preferably override <code>onCancelled(Object)</code>.
 This method is invoked by the default implementation of
 <code>onCancelled(Object)</code>.</p>
 <p>Runs on the UI thread after <code>cancel(boolean)</code> is invoked and
 <code>doInBackground(Object[])</code> has finished.</p>
 */
- (void)onCancelled;

/*!
 @brief <p>Runs on the UI thread after <code>cancel(boolean)</code> is invoked and
 <code>doInBackground(Object[])</code> has finished.
 </p>
 <p>The default implementation simply invokes <code>onCancelled()</code> and
 ignores the result. If you write your own implementation, do not call
 <code>super.onCancelled(result)</code>.</p>
 @param result The result, if any, computed in
 <code>doInBackground(Object[])</code>, can be null
 */
- (void)onCancelledWithId:(id)result;

/*!
 @brief <p>Runs on the UI thread after <code>doInBackground</code>.
 The
 specified result is the value returned by <code>doInBackground</code>.</p>
 <p>This method won't be invoked if the task was cancelled.</p>
 @param result The result of the operation computed by <code>doInBackground</code>.
 */
- (void)onPostExecuteWithId:(id)result;

/*!
 @brief Runs on the UI thread before <code>doInBackground</code>.
 */
- (void)onPreExecute;

/*!
 @brief Runs on the UI thread after <code>publishProgress</code> is invoked.
 The specified values are the values passed to <code>publishProgress</code>.
 @param values The values indicating progress.
 */
- (void)onProgressUpdateWithNSObjectArray:(IOSObjectArray *)values;

/*!
 @brief This method can be invoked from <code>doInBackground</code> to
 publish updates on the UI thread while the background computation is
 still running.
 Each call to this method will trigger the execution of
 <code>onProgressUpdate</code> on the UI thread.
 <code>onProgressUpdate</code> will not be called if the task has been
 canceled.
 @param values The progress values to update the UI with.
 */
- (void)publishProgressWithNSObjectArray:(IOSObjectArray *)values;

@end

J2OBJC_STATIC_INIT(AndroidOsAsyncTask)

FOUNDATION_EXPORT id<JavaUtilConcurrentExecutor> AndroidOsAsyncTask_THREAD_POOL_EXECUTOR_;
J2OBJC_STATIC_FIELD_GETTER(AndroidOsAsyncTask, THREAD_POOL_EXECUTOR_, id<JavaUtilConcurrentExecutor>)

FOUNDATION_EXPORT id<JavaUtilConcurrentExecutor> AndroidOsAsyncTask_SERIAL_EXECUTOR_;
J2OBJC_STATIC_FIELD_GETTER(AndroidOsAsyncTask, SERIAL_EXECUTOR_, id<JavaUtilConcurrentExecutor>)

FOUNDATION_EXPORT void AndroidOsAsyncTask_setDefaultExecutorWithJavaUtilConcurrentExecutor_(id<JavaUtilConcurrentExecutor> exec);

FOUNDATION_EXPORT void AndroidOsAsyncTask_init(AndroidOsAsyncTask *self);

FOUNDATION_EXPORT void AndroidOsAsyncTask_executeWithJavaLangRunnable_(id<JavaLangRunnable> runnable);

J2OBJC_TYPE_LITERAL_HEADER(AndroidOsAsyncTask)

typedef NS_ENUM(NSUInteger, AndroidOsAsyncTask_Status) {
  AndroidOsAsyncTask_Status_PENDING = 0,
  AndroidOsAsyncTask_Status_RUNNING = 1,
  AndroidOsAsyncTask_Status_FINISHED = 2,
};

/*!
 @brief Indicates the current status of the task.
 Each status will be set only once
 during the lifetime of a task.
 */
@interface AndroidOsAsyncTask_StatusEnum : JavaLangEnum < NSCopying >

#pragma mark Package-Private

+ (IOSObjectArray *)values;
FOUNDATION_EXPORT IOSObjectArray *AndroidOsAsyncTask_StatusEnum_values();

+ (AndroidOsAsyncTask_StatusEnum *)valueOfWithNSString:(NSString *)name;
FOUNDATION_EXPORT AndroidOsAsyncTask_StatusEnum *AndroidOsAsyncTask_StatusEnum_valueOfWithNSString_(NSString *name);

- (id)copyWithZone:(NSZone *)zone;

@end

J2OBJC_STATIC_INIT(AndroidOsAsyncTask_StatusEnum)

FOUNDATION_EXPORT AndroidOsAsyncTask_StatusEnum *AndroidOsAsyncTask_StatusEnum_values_[];

#define AndroidOsAsyncTask_StatusEnum_PENDING AndroidOsAsyncTask_StatusEnum_values_[AndroidOsAsyncTask_Status_PENDING]
J2OBJC_ENUM_CONSTANT_GETTER(AndroidOsAsyncTask_StatusEnum, PENDING)

#define AndroidOsAsyncTask_StatusEnum_RUNNING AndroidOsAsyncTask_StatusEnum_values_[AndroidOsAsyncTask_Status_RUNNING]
J2OBJC_ENUM_CONSTANT_GETTER(AndroidOsAsyncTask_StatusEnum, RUNNING)

#define AndroidOsAsyncTask_StatusEnum_FINISHED AndroidOsAsyncTask_StatusEnum_values_[AndroidOsAsyncTask_Status_FINISHED]
J2OBJC_ENUM_CONSTANT_GETTER(AndroidOsAsyncTask_StatusEnum, FINISHED)

J2OBJC_TYPE_LITERAL_HEADER(AndroidOsAsyncTask_StatusEnum)

#endif // _AndroidOsAsyncTask_H_