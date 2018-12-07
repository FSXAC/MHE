/* State design pattern is useful for state machines
 * allowing objects to be in different states for different roles / outputs
 * 
 * 
 * Checklist:
 * 1. Use existing or new class as the state machine as a wrapper for the client
 * 2. Create State base class that replicates methods of the state machine interface
 * 3. Create state derived class for each domain state
 * 4. Wrapper class maintains a current state
 * 5. Client talks with wrapper state machine class, logic is delegated to current
 *    state object
 * 6. 
 * 
 * Source:
 * - https://sourcemaking.com/design_patterns/state
 * - CPEN 211/311 knowledge
 */