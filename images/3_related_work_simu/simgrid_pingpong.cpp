#include <simgrid/s4u.hpp>

XBT_LOG_NEW_DEFAULT_CATEGORY(example, "Messages relative to the ping-pong");

using namespace simgrid; // Allows us to use s4u:: instead of simgrid::s4u::

static void initiator(std::vector<std::string> args) {
  xbt_assert(args.size() > 1, "The initiator expects 1 argument");

  int ping_pong_max_size = std::stol(args[1]);

  s4u::Mailbox *target = s4u::Mailbox::by_name("target_mbx");
  s4u::Mailbox *my_mailbox = s4u::Mailbox::by_name("initiator_mbx");

  int iteration = 0;
  for (int size = 1; size <= ping_pong_max_size; size *= 2) {
    XBT_INFO("Sending ping of size %d", size);
    target->put(new int(iteration), size); // Send ping
    std::unique_ptr<int> pong = my_mailbox->get_unique<int>(); // Wait for pong
    xbt_assert(*pong == iteration); // Check that the pong data is the current iteration
    XBT_INFO("Pong (sequence = %d)", *pong);
    iteration++;
  }
}

static void target(std::vector<std::string> args) {
  xbt_assert(args.size() > 1, "The target expects 1 argument");

  s4u::Actor::self()->daemonize(); // Get killed automatically when initiator is done

  int ping_pong_max_size = std::stol(args[1]);
  s4u::Mailbox *my_mailbox = s4u::Mailbox::by_name("target_mbx");
  s4u::Mailbox *initiator = s4u::Mailbox::by_name("initiator_mbx");

  int size = 1;
  for (;;) { // Safe endless loop because this Actor is a daemon
    std::unique_ptr<int> ping_data = my_mailbox->get_unique<int>(); // Wait for ping
    initiator->put(new int(*ping_data), size); // Send pong with the iteration number received
    size *= 2;
  }
}

int main(int argc, char* argv[])
{
  s4u::Engine e(&argc, argv);
  xbt_assert(argc > 2, "Usage: %s platform_file deployment_file\n", argv[0]);

  /* Register the functions representing the Actors */
  e.register_function("initiator", &initiator);
  e.register_function("target", &target);

  /* Load the platform description and then deploy the application */
  e.load_platform(argv[1]);
  e.load_deployment(argv[2]);

  /* Run the simulation */
  e.run();

  XBT_INFO("Simulation is over");

  return 0;
}