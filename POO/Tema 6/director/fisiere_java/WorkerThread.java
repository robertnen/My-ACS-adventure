// private class WorkerThread extends Thread {
//     public void run() {
//         try {
//             while (running) {
//                 Runnable task = taskQueue.poll(); // Get a task from the queue.
//                 if (task == null)
//                     break; // (because the queue is empty)
//                 task.run();  // Execute the task;
//             }
//         }
//         finally {
//             threadFinished(); // Records fact that this thread has terminated.
//         }
//     }
// }