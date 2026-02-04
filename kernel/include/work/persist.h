#ifndef PERSIST_H
#define PERSIST_H

/**
 * @brief Runs a binary with root perms
 *
 * @param binary_path Path to the binary to persist
 * @param argv nessasary argv for the persisted binary
 * @return int 0 on success, 1 on failure
 */
int PersistBinary(const char *binary_path, const char *argv);

#endif