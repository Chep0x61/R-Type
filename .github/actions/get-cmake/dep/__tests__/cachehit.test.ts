// Copyright (c) 2020 Luca Cappa
// Released under the term specified in file LICENSE.txt
// SPDX short identifier: MIT

import * as process from 'process';
import * as os from 'os';
import { ToolsGetter } from '../src/get-cmake';
import * as cache from '@actions/cache';

jest.setTimeout(15 * 1000)

jest.mock('@actions/tool-cache');

const cacheSaveCache = jest.spyOn(cache, 'saveCache').mockImplementation(() =>
    Promise.resolve(0)
);

const cacheRestoreCache = jest.spyOn(cache, 'restoreCache').mockImplementation(() =>
    Promise.resolve("key")
);

test('testing dep with cache-hit...', async () => {
    process.env.RUNNER_TEMP = os.tmpdir();
    const getter: ToolsGetter = new ToolsGetter();
    await getter.run();
    expect(cacheSaveCache).toBeCalledTimes(0);
    expect(cacheRestoreCache).toBeCalledTimes(1);
});
