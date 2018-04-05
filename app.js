// Logic for standin backend.
const standin = require('./build/Release/standin');

// For now call it each time a new frame is pushed to the queue.
// It may be more efficient to wait for a chunk of frames before starting.
module.exports = function(context, dataTrigger, oldState, count) {
  var standinInput = {oldState: oldState, count: count, data: dataTrigger};
  var standinOutput = standin.Parse(standinInput)

  // Preserve state information for next call.
  context.output.count = standinOutput.count;
  context.output.oldState = standinOutput.oldState;

  // Check if a sign has been returned.
  if (standinOutput.hasOwnProperty('result')) {
    context.done(null, standinOutput.result);
  }

  context.done(null, null);
};
