/* Copyright (C) 2016 Red Hat, inc.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Jakub Filak <jfilak@redhat.com>
 */
#include <systemd/sd-journal.h>

#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <assert.h>

#define SD_MESSAGE_FIELD "MESSAGE="

int main(int argc, char *argv[])
{
    if (argc == 0) {
        errx(EXIT_FAILURE, "Usage:\n  %s MESSAGE [FILED=VALUE,...]\n", argv[0]);
    }

    const size_t messagelen = strlen(SD_MESSAGE_FIELD) + strlen(argv[1]) + 1;
    char *const message = malloc(messagelen);
    if (message == NULL) {
        err(EXIT_FAILURE, "Cannot allocate memory for message");
    }

    assert(snprintf(message, messagelen, SD_MESSAGE_FIELD"%s", argv[1]) < (int)messagelen);

    const size_t itemscnt = argc - 1;
    struct iovec entry[itemscnt];
    entry[0].iov_base = message;
    entry[0].iov_len = messagelen - 1;

    struct iovec *iter = &entry[1];
    for (size_t i = 2; i <= itemscnt; ++i, ++iter) {
        iter->iov_base = argv[i];
        iter->iov_len = strlen(argv[i]);
    }

    sd_journal_sendv(entry, itemscnt);

    free(message);

    return EXIT_SUCCESS;
}
