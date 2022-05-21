#include <PageContainer.hpp>
#include <Parser.hpp>

int main(int argc, char* argv[]) {
  Log the_log(LOG_ENABLE);
  UsedMemory used_memory(the_log);
  Arguments arguments = parse_arguments(argc, argv);;

  std::cout << arguments.filename << " " << arguments.threshold << "\n";

  PageContainer page(the_log, &used_memory);
  std::ifstream in(arguments.filename);
  page.Load(in, arguments.threshold);

  the_log.Write(std::to_string(used_memory.get_used()));

  for (size_t i = 0; i < 5; ++i)
  {
    const auto& item = page.ByIndex(i);
    std::cout << item.name << ": " << item.score << std::endl;
    const auto& item2 = page.ById(std::to_string(i));
    std::cout << item2.name << ": " << item2.score << std::endl;
  }

  page.Reload(arguments.threshold);
  the_log.Write(std::to_string(used_memory.get_used()));

  return 0;
}